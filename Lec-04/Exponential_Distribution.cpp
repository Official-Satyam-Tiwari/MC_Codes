#include <iostream>
#include <TMath.h>
#include <TRandom3.h>
#include <TH1D.h>
#include <TCanvas.h>

void generate_and_plot_exponential(int n, double lambda) {
    TRandom3 randGen(5); // Random number generator with seed 5

    // Create a histogram to hold the values
    TH1D* hist = new TH1D("hist", "Exponential Distribution", 50, 0, 10);  // 50 bins, range from 0 to 10

    // Generate n random numbers from the exponential distribution
    for (int i = 0; i < n; ++i) {
        double u = randGen.Rndm();  // Uniform random number in [0, 1]
        double x = -TMath::Log(1 - u) / lambda;  // Inverse transform sampling for exponential distribution

        hist->Fill(x);  // Fill the histogram with the generated value
    }

    // Create a canvas to plot the histogram
    TCanvas* c1 = new TCanvas("c1", "Random Numbers from Exponential Distribution", 800, 600);
    hist->SetXTitle("Value");
    hist->SetYTitle("Frequency");
    hist->SetLineColor(kBlue);  // Set line color for histogram
    hist->Draw();  // Draw the histogram

    // Display the canvas
    c1->Update();
}

int main() {
    int n = 10000;          // Number of random numbers to generate
    double lambda = 1.0;    // Rate parameter of the exponential distribution
    generate_and_plot_exponential(n, lambda);  // Generate and plot n random numbers

    return 0;
}