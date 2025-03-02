#include <iostream>
#include <cmath>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TGraph.h>

using namespace std;

// Function to calculate scattered energy
double scattered_energy(double E, double theta) {
    double me_c2 = 511.0; // Electron rest energy in keV
    return E / (1 + E * (1 - cos(theta)) / me_c2);
}

// Function to calculate differential cross-section
double diff_cross_section(double E, double theta) {
    double r_e = 2.817e-15; // Classical electron radius in meters
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
        f = diff_cross_section(E, theta) ;
    } while (f>f_max); // Accept if random number <= f
    return theta;
}

// Plot histogram of scattered angles
void plot_scattered_energy() {
    TCanvas *c1 = new TCanvas("c1", "Scattered Angles", 800, 600);
    TH1F *h1 = new TH1F("h1", "Scattered Angles", 100, 0, 2*M_PI);

    for (int i = 0; i < 100000; i++) {
        double theta = angle_from_klein_nishina(2024); // Incident energy in keV
        h1->Fill(theta);
    }

    h1->SetXTitle("Theta (radians)");
    h1->SetYTitle("Counts");
    h1->Draw();
}

// Plot theta vs scattered energy
void plot_theta_vs_Scattered_Energy() {
    TCanvas *c2 = new TCanvas("c2", "Theta vs Scattered Energy", 800, 600);
    TGraph *graph = new TGraph();

    for (int i = 0; i < 10000; i++) {
        double theta = i * M_PI / 10000.0; // Uniformly sample theta
        double E_prime = scattered_energy(511, theta); // Incident energy in keV
        graph->SetPoint(i, theta, E_prime);
    }

    graph->SetTitle("Theta vs Scattered Energy");
    graph->GetXaxis()->SetTitle("Theta (radians)");
    graph->GetYaxis()->SetTitle("Scattered Energy (keV)");
    graph->Draw("AP");
}

// Plot theta vs differential cross-section
void plot_theta_vs_f() {
    TCanvas *c3 = new TCanvas("c3", "Theta vs Differential Cross Section", 800, 600);
    TGraph *graph = new TGraph();

    for (int i = 0; i < 10000; i++) {
        double theta = i * M_PI / 10000.0; // Uniformly sample theta
        double f = diff_cross_section(511, theta); // Incident energy in keV
        graph->SetPoint(i, theta, f);
    }

    graph->SetTitle("Theta vs Differential Cross Section");
    graph->GetXaxis()->SetTitle("Theta (radians)");
    graph->GetYaxis()->SetTitle("Diff Cross Section");
    graph->Draw("AP");
}