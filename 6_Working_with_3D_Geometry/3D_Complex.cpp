#include <TGraph.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>

const double m_e_kev = 511.0; // Electron mass in keV
const double E_gamma = 511.0; // Incident photon energy in keV

double SimulateDistance(double lambda, TRandom3& random) {
    double r = random.Uniform(0, 1);
    return -log(1 - r) / lambda;
}

double KleinNishina(double E, double theta) {
    const double re = 2.817e-13; // Classical electron radius (cm)
    const double mec2 = 0.511;   // Electron rest energy (MeV)
    double cosTheta = cos(theta);
    double E_prime = E / (1 + (E / mec2) * (1 - cosTheta));
    double ratio = E_prime / E;
    return 0.5 * re * re * ratio * ratio * (ratio + 1/ratio - pow(sin(theta), 2));
}

double simulateTheta(double E_gamma, TRandom3& random) {
    double f_max = KleinNishina(E_gamma, 0); // Maximum at θ=0
    while (true) {
        double theta = random.Uniform(0, TMath::Pi());
        double f = random.Uniform(0, f_max);
        if (f < KleinNishina(E_gamma, theta)) return theta;
    }
}

double SimulateElectronEnergy(double E_gamma, TRandom3& random) {
    double theta = simulateTheta(E_gamma, random);
    double E_scattered = E_gamma / (1 + (E_gamma / m_e_kev) * (1 - cos(theta)));
    return E_gamma - E_scattered;
}

double simulate_th(TRandom3& random) {
    return acos(random.Uniform(-1, 1));
}

double theoretical_efficiency() {
    double lambda = 0.5;  // cm⁻¹
    double d = 2.0;       // cm
    double b = 10.0;      // cm
    double r0 = 40.0;     // cm

    double c = atan((b/2) / r0); // Angular half-width
    double F = 1 - exp(-lambda * d); // Interaction probability

    double theta1 = TMath::Pi()/2 - c;
    double theta2 = TMath::Pi()/2 + c;
    double phi1 = -c;
    double phi2 = c;

    double f_geo = (phi2 - phi1) * (cos(theta1) - cos(theta2)) / (4.0 * TMath::Pi());
    return 4.0*f_geo * F;
}

double efficiency(double E_thresh = 0.0) {
    TRandom3 random;
    random.SetSeed(0);

    int N_acc = 0;
    int N_steps = 10000;
    double lambda = 0.5;  // cm⁻¹
    double d = 2.0;       // cm
    double b = 10.0;      // cm
    double r0 = 40.0;     // cm

    double c = atan((b/2.0) / r0);

    for (int i = 0; i < N_steps; ++i) {
        double theta = simulate_th(random);
        double phi = random.Uniform(0, 2*TMath::Pi());

        if (theta >= (TMath::Pi()/2 - c) && theta <= (TMath::Pi()/2 + c)) {
            if ((phi >= 0 && phi <= c) || (phi >= 2*TMath::Pi() - c && phi <= 2*TMath::Pi()) || // X-axis detector (wrapped)
                (phi >= TMath::Pi() - c && phi <= TMath::Pi() + c) || // -X-axis detector
                (phi >= TMath::Pi()/2 - c && phi <= TMath::Pi()/2 + c) || // Y-axis detector
                (phi >= 3*TMath::Pi()/2 - c && phi <= 3*TMath::Pi()/2 + c) // -Y-axis detector
                ) {
                
                double path_length = d / cos(theta);
                double r = SimulateDistance(lambda, random);

                if (r <= path_length) {
                    double E_electron = SimulateElectronEnergy(E_gamma, random);
                    if (E_electron >= E_thresh) N_acc++;
                }
            }
        }
    }

    double eff = (double)N_acc / N_steps;
    double sd = sqrt(eff / N_steps);

    double p_error = 100 * abs(theoretical_efficiency() - eff) / theoretical_efficiency();

    cout << "Theoretical Efficiency: " << theoretical_efficiency() << endl;
    cout << "Simulated Efficiency: " << eff << endl;
    cout << "Standard Deviation: " << sd << endl;
    cout << "Percentage Error (%): " << p_error << endl;

    return eff;
}

//Optional
void histogram_of_theta() {
    TRandom3 random;
    TH1F* hist = new TH1F("theta", "Theta Distribution", 100, 0, 2*TMath::Pi());

    for (int i = 0; i < 100000; ++i) {
        //double theta = simulateTheta(0.511,random);
        double theta = simulate_th(random);
        hist->Fill(theta); //It's correct it should be bell shaped and not uniform distribution
    }

    TCanvas* c = new TCanvas("c", "Theta", 800, 600);
    hist->Draw();
}