#include <iostream>
#include <cmath>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TGraph.h>

using namespace std;

const double m_e_kev = 511.0; // Electron rest energy in keV
const double r_e = 2.817e-15; // Classical electron radius in meters

// Function to calculate scattered energy
double scattered_energy(double E, double theta) {
    return E / (1 + E * (1 - cos(theta)) / m_e_kev);
}

// Function to calculate differential cross-section
double diff_cross_section(double E, double theta) {
    double E_prime = scattered_energy(E, theta);
    double term1 = (r_e * r_e / 2) * pow(E_prime / E, 2);
    double term2 = (E_prime / E + E / E_prime - pow(sin(theta), 2));
    return term1 * term2;
}

// Function to sample theta using Klein-Nishina distribution
double angle_from_klein_nishina(double E) {
    TRandom3 random;
    random.SetSeed(0);

    double theta, f, f_max = diff_cross_section(E, 0.0); // Maximum at theta = 0
    do {
        theta = random.Uniform(0, M_PI); // Physical scattering angles (0 to π)
        f = diff_cross_section(E, theta);
    } while (f > f_max); // Accept if random number <= f
    return theta;
}

// Function to simulate scattered electron energy
double simulate_electron_energy(double E_gamma) {
    double theta = angle_from_klein_nishina(E_gamma);
    double E_scattered = scattered_energy(E_gamma, theta);
    return E_gamma - E_scattered;
}

// Plot histogram of scattered electron energies
void plot_scattered_energy(double E_gamma, int nSteps) {
    TCanvas *c = new TCanvas("c", "Energy Distribution of Scattered Electrons", 800, 600);
    TH1F *hist = new TH1F("hist", "Energy Distribution of Scattered Electrons; Energy (keV); Counts", 100, 0, E_gamma);

    for (int i = 0; i < nSteps; ++i) {
        double E_electron = simulate_electron_energy(E_gamma);
        hist->Fill(E_electron);
    }

    hist->Draw();
}

// Main function
int main() {
    double E_gamma = 511.0; // Incident photon energy in keV
    int nSteps = 10000; // Number of events to simulate

    plot_scattered_energy(E_gamma, nSteps);

    return 0;
}
