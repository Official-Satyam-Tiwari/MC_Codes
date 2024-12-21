#include <iostream>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TGraph2D.h>

void generate_random_points(int n, double radius) {
    TRandom3 randGen(4);  // Random number generator with seed 4

    // Create a TGraph2D to hold the points
    TGraph2D* graph = new TGraph2D();

    // Generate n random points inside the sphere
    for (int i = 0; i < n; ++i) {
        // Step 1: Generate a random value for r
        double u = randGen.Rndm();  // Uniform random number in [0, 1]
        double r = radius * TMath::Power(u, 1.0/3.0);  // Inverse CDF for uniform volume distribution

        // Step 2: Generate random values for theta and phi
        double v = randGen.Rndm();  // Uniform random number in [0, 1]
        double theta = TMath::ACos(1 - 2 * v);  // Uniform theta from 0 to pi

        double w = randGen.Rndm();  // Uniform random number in [0, 1]
        double phi = 2 * TMath::Pi() * w;  // Uniform phi from 0 to 2*pi

        // Step 3: Convert spherical to Cartesian coordinates
        double x = r * TMath::Sin(theta) * TMath::Cos(phi);
        double y = r * TMath::Sin(theta) * TMath::Sin(phi);
        double z = r * TMath::Cos(theta);

        // Add the point to the graph
        graph->SetPoint(i, x, y, z);
    }

    // Step 4: Plot the points in 3D
    TCanvas* c1 = new TCanvas("c1", "Random Points Inside a Sphere", 800, 600);
    graph->Draw("P");  // "P" for points

    // Display the canvas
    c1->Update();
}

void generate_and_plot_points() {
    int n = 1000;  // Number of points to generate
    double radius = 1.0;  // Example radius of the sphere
    generate_random_points(n, radius);  // Generate and plot n random points inside the sphere
}

int main() {
    generate_and_plot_points();
    return 0;
}