#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>
#include <TAxis.h>
#include <TH1F.h>
#include <TRandom3.h>

// Constants
const double re = 2.817e-13; // Classical electron radius in cm
const double mec2 = 0.511;   // Electron rest energy in MeV

// Klein-Nishina formula
double KleinNishina(double E, double theta) {
    double cosTheta = TMath::Cos(theta);
    double E_prime = E / (1 + (E / mec2) * (1 - cosTheta));
    double ratio = E_prime / E;
    return 0.5 * re * re * ratio * ratio * (ratio + 1 / ratio - TMath::Sin(theta) * TMath::Sin(theta));
}

// Scattered photon energy
double ScatteredEnergy(double E, double theta) {
    double cosTheta = TMath::Cos(theta);
    return E / (1 + (E / mec2) * (1 - cosTheta));
}

void plot_theta_kn() {
    int n = 10000; // Number of Points
    double E = 0.1; // Incident photon energy in MeV
    double f_max = KleinNishina(E, 0); // Maximum value of the Klein-Nishina formula at theta = 0
            
    TRandom3 random;
    random.SetSeed(0);

    // Histogram
    TH1F *hist = new TH1F("Theta", "Theta Distribution from KN;Theta;Count", 100, 0, TMath::Pi()*2);

    for (int i = 0; i < n; i++) {
        bool accepted = false;

        while (!accepted) {
            double theta = random.Uniform(0, TMath::Pi()); // Scattering angle in radians
            double f = random.Uniform(0, f_max);
            double f_theta = KleinNishina(E, theta);

            if (f < f_theta) {
                accepted = true;
                hist->Fill(theta);
            }
        }
    }

    TCanvas *canvas = new TCanvas("Theta", "n_theta Plot", 800, 600);
    hist->Draw();
}

void plot_E_electron() {
    int n = 10000; // Number of Points
    double E = 1; // Incident photon energy in MeV
    double f_max = KleinNishina(E, 0); // Maximum value of the Klein-Nishina formula at theta = 0
            
    TRandom3 random;
    random.SetSeed(0);

    // Histogram
    TH1F *hist = new TH1F("Energy", "Electron Energy Distribution from KN;E;Count", 100, 0, 1);

    for (int i = 0; i < n; i++) {
        bool accepted = false;

        while (!accepted) {
            double theta = random.Uniform(0, TMath::Pi()); // Scattering angle in radians
            double f = random.Uniform(0, f_max);
            double f_theta = KleinNishina(E, theta);

            if (f < f_theta) {
                accepted = true;
                double electron_energy = E - ScatteredEnergy(E, theta);
                hist->Fill(electron_energy);
            }
        }
    }

    TCanvas *canvas = new TCanvas("Energy", "Electron Energy Plot", 800, 600);
    hist->Draw();
}
