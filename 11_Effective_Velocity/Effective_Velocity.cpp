const double M_E_KEV = 511.0;  // Electron mass in keV
const double E_GAMMA = 511.0;  // Incident photon energy in keV

// Simulate distance using exponential distribution
double SimulateDistance(double lambda, TRandom3& random) {
    return -std::log(random.Uniform()) / lambda;
}

void PlotTimeDifference() {
    TRandom3 random(0);

    const double LAMBDA = 0.5;    // Absorption coefficient in cm^-1
    const double D = 2.0;         // Detector thickness in cm
    const double R0 = 40.0;       // Detector radius in cm
    const double N = 1.5;         // Refractive index
    const double L = 50.0;        // Detector length in cm
    const int N_STEPS = 1000000;    // Number of simulated events
    const double C = 3e10;        // Speed of light in cm/s

    TCanvas *c = new TCanvas("c", "Effective Velocity", 1200, 800);
    TH1D *h1 = new TH1D("Eff_Vel", "t_{A} - t_{B};Time Difference [ns];Counts", 100, -10, 10);

    const double THETA_MAX = atan(L / (2 * R0));

    int filled = 0;
    while(filled < N_STEPS) {
        double theta = random.Uniform(0, 2*TMath::Pi());
        double r = SimulateDistance(LAMBDA, random);

        bool hitsDetector = (theta < THETA_MAX || theta > 2*TMath::Pi() - THETA_MAX);
        bool withinThickness = (r * cos(theta) < D);

        if (withinThickness && hitsDetector) {
            double z = R0 * tan(theta);
            
            double dA = L/2 - z;  // Distance to PMT A
            double dB = L/2 + z;  // Distance to PMT B

            double tA = dA * N / C;
            double tB = dB * N / C;
            double t_diff_ns = (tA - tB) * 1e9;

            filled++;
            h1->Fill(t_diff_ns);
        }
    }
}