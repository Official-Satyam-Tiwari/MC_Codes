#include <TGraph.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <cmath>
#include <iostream>

// Constants
const double m_e_kev = 511.0; // Electron mass in keV
const double E_gamma = 511.0; // Incident photon energy in keV
const double lambda = 0.5;    // Decay constant in cm^-1
const double d = 2.0;         // Detector thickness in cm
const int N_steps = 10000;    // Number of simulation steps

// Global random number generator
TRandom3 rng(0); // Seed with 0 for reproducibility

// Simulate distance using exponential distribution
double SimulateDistance(double lambda) {
    return rng.Exp(1 / lambda);
}

// Simulate electron energy after scattering
double SimulateElectronEnergy(double E_gamma) {
    double theta = rng.Uniform(0, 2 * M_PI); // Random scattering angle
    double E_scattered = E_gamma / (1 + E_gamma / m_e_kev * (1 - cos(theta)));
    return E_gamma - E_scattered; // Electron energy
}

// Calculate efficiency for a given energy threshold
double efficiency(double E_thresh, int N_steps = 10000, double lambda = 0.5, double d = 2.0) {
    int N_acc = 0;

    for (int i = 0; i < N_steps; ++i) {
        double r = SimulateDistance(lambda);
        double E_electron = SimulateElectronEnergy(E_gamma);

        if (r < d && E_electron >= E_thresh) {
            N_acc++;
        }
    }

    return static_cast<double>(N_acc) / N_steps;
}

// Plot efficiency vs energy threshold
void EfficiencyVsEthresh() {
    const int nPoints = 350;
    double E_thresh = 0.0;

    TGraph* graph = new TGraph();
    graph->SetTitle("Efficiency vs Energy Threshold;Energy Threshold (keV);Efficiency");

    for (int i = 0; i < nPoints; ++i) {
        double eff = efficiency(E_thresh);
        graph->SetPoint(i, E_thresh, eff);
        E_thresh += 1.0;
    }

    TCanvas* c1 = new TCanvas("c1", "Efficiency vs Energy Threshold", 800, 600);
    graph->Draw("AL");
}

// Plot histogram of simulated distances
void histogram_simulate_distance() {
    const int nPoints = 10000;

    TH1D* h = new TH1D("Distance Distribution", "Distance", 100, 0, 10); // 100 bins from 0 to 10 cm

    for (int i = 0; i < nPoints; ++i) {
        double r = SimulateDistance(lambda);
        h->Fill(r);
    }

    TCanvas* c = new TCanvas("c", "Distance Distribution", 800, 600); // 800x600 pixels
    h->Draw();
}