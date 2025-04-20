#include "header.h"
#include <TGraph.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <cmath>
#include <iostream>

// Constants
const double m_e_kev = 511.0; // Electron mass in keV
const double E_gamma = 511.0; // Incident photon energy in keV
const double re = 2.817e-13;  // Classical electron radius in cm
const double mec2 = 0.511;    // Electron rest energy in MeV

// Global random number generator
TRandom3 rng(0); // Seed with 0 for reproducibility

// Inverse transform sampling for exponential distribution
double SimulateDistance(double lambda) {
    double r = rng.Uniform(0, 1);
    return -log(1 - r) / lambda;
}

// Klein-Nishina formula
double KleinNishina(double E, double theta) {
    double cosTheta = TMath::Cos(theta);
    double E_prime = E / (1 + (E / mec2) * (1 - cosTheta));
    double ratio = E_prime / E;
    return 0.5 * re * re * ratio * ratio * (ratio + 1 / ratio - TMath::Sin(theta) * TMath::Sin(theta));
}

// Simulate scattering angle using Klein-Nishina formula
double simulateTheta(double E_gamma) {
    double f_max = KleinNishina(E_gamma, 0); // Maximum value at theta = 0
    double accepted_theta;

    while (true) {
        double theta = rng.Uniform(0, TMath::Pi()); // Scattering angle in radians
        double f = rng.Uniform(0, f_max);
        double f_theta = KleinNishina(E_gamma, theta);

        if (f < f_theta) {
            accepted_theta = theta;
            break;
        }
    }

    return accepted_theta;
}

// Simulate electron energy after scattering
double SimulateElectronEnergy(double E_gamma) {
    double theta = simulateTheta(E_gamma); // Scattering angle
    double E_scattered = E_gamma / (1 + E_gamma / m_e_kev * (1 - cos(theta)));
    return E_gamma - E_scattered; // Electron energy
}

// Calculate efficiency for a given energy threshold
double efficiency(double E_thresh, double lambda = 0.5, double d = 2.0, int N_steps = 10000) {
    int N_acc = 0;

    for (int i = 0; i < N_steps; ++i) {
        double r1 = SimulateDistance(lambda);
        double r2 = SimulateDistance(lambda);

        if (r1 < d && r2 < d) {
            double E_electron1 = SimulateElectronEnergy(E_gamma);
            double E_electron2 = SimulateElectronEnergy(E_gamma);

            if (E_electron1 >= E_thresh && E_electron2 >= E_thresh) {
                N_acc++;
            }
        }
    }

    return static_cast<double>(N_acc) / N_steps;
}

// Plot efficiency vs energy threshold
void EfficiencyVsEthresh() {
    const int nPoints = 50;
    double E_thresh = 0.0;

    TGraph *graph = new TGraph();
    graph->SetTitle("Efficiency vs Energy Threshold;Energy Threshold (keV);Efficiency");

    for (int i = 0; i < nPoints; ++i) {
        double eff = efficiency(E_thresh);
        graph->SetPoint(i, E_thresh, eff);
        E_thresh += 1.0;
    }

    TCanvas *c1 = new TCanvas("c1", "Efficiency vs Energy Threshold", 800, 600);
    graph->Draw("AL");
}