#include <TGraph.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

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

// Wrap angle to [0, 2π)
void WrapAngle(double& angle) {
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0) {
        angle += 2 * M_PI;
    }
}

// Calculate module angular ranges
void CalculateModuleAngles(int n, double b, double r0, vector<double>& phi_min, vector<double>& phi_max) {
    double delta_phi = 2 * M_PI / n; // Angular spacing between module centers
    double delta = atan(0.5 * b / r0); // Angular half-width of a module

    phi_min.clear();
    phi_max.clear();

    for (int i = 0; i < n; ++i) {
        double phi_center = i * delta_phi;
        double phi_min_i = phi_center - delta;
        double phi_max_i = phi_center + delta;

        WrapAngle(phi_min_i); // Ensure angle is in [0, 2π)
        WrapAngle(phi_max_i);

        phi_min.push_back(phi_min_i);
        phi_max.push_back(phi_max_i);
    }
}

// Calculate efficiency for a single detector configuration
double complex_efficiency(int n, double b, double r0, double d, double lambda, int N_steps) {
    vector<double> phi_min, phi_max;
    CalculateModuleAngles(n, b, r0, phi_min, phi_max);

    int N_acc = 0;

    for (int i = 0; i < N_steps; ++i) {
        double phi = rng.Uniform(0, 2 * M_PI);
        double chi = fmod(phi + M_PI, 2 * M_PI); // Ensure chi is 180° apart from phi

        bool phi_in_range = false;
        bool chi_in_range = false;

        // Check if phi and chi are within any detector's range
        for (int j = 0; j < n; ++j) {
            if (phi_min[j] < phi && phi < phi_max[j]) {
                phi_in_range = true;
            }
            if (phi_min[j] < chi && chi < phi_max[j]) {
                chi_in_range = true;
            }
        }

        // Check if phi and chi satisfy all conditions
        if (phi_in_range && chi_in_range) {
            double r1 = SimulateDistance(lambda);
            double r2 = SimulateDistance(lambda);

            if (r1 * cos(phi) < d && r2 * cos(chi) < d) {
                N_acc++;
            }
        }
    }

    return static_cast<double>(N_acc) / N_steps;
}

// Plot efficiency vs number of detectors
void EfficiencyVsDetectors() {
    double r0 = 40.00; // in cm
    double b = 10.00; // in cm
    double d = 2.00; // in cm
    double lambda = 0.5; // in cm^-1
    int N_steps = 1000;

    const int max_detectors = 100;
    double detectors[max_detectors];
    double efficiencies[max_detectors];

    for (int n = 1; n <= max_detectors; ++n) {
        detectors[n - 1] = n;
        efficiencies[n - 1] = complex_efficiency(n, b, r0, d, lambda, N_steps);
        cout << "Efficiency for " << n << " detectors: " << efficiencies[n - 1] << endl;
    }

    TGraph* graph = new TGraph(max_detectors, detectors, efficiencies);
    graph->SetTitle("Efficiency vs Number of Detectors;Number of Detectors;Efficiency");
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);
    graph->SetLineWidth(2);
    graph->SetLineColor(kRed);

    TCanvas* canvas = new TCanvas("canvas", "Efficiency vs Number of Detectors", 800, 600);
    graph->Draw("APL");
}