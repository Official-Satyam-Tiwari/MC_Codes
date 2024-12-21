#include <iostream>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TGraph.h>

void generate_random_points_in_circle(int n, double radius) {
    TRandom3 randGen(2);  // Random number generator with seed 2

    // Create a TGraph to hold the points
    TGraph* graph = new TGraph();

    // Generate n random points inside the circle
    for (int i = 0; i < n; ++i) {
        // Step 1: Generate a random value for the radial distance
        double u = randGen.Rndm();  // Uniform random number in [0, 1]
        double r = radius * TMath::Sqrt(u);  // Inverse CDF for uniform area distribution

        // Step 2: Generate a random angle
        double v = randGen.Rndm();  // Uniform random number in [0, 1]
        double theta = 2 * TMath::Pi() * v;  // Uniform angle from 0 to 2*pi

        // Step 3: Convert polar coordinates to Cartesian coordinates
        double x = r * TMath::Cos(theta);
        double y = r * TMath::Sin(theta);

        // Add the point to the graph
        graph->SetPoint(i, x, y);
    }

    // Step 4: Plot the points in 2D
    TCanvas* c1 = new TCanvas("c1", "Random Points Inside a Circle", 800, 600);
    graph->SetMarkerStyle(20);  // Set marker style to circle
    graph->SetMarkerColor(kBlue);  // Set marker color to blue
    graph->Draw("AP");  // "A" for axes, "P" for points

    // Display the canvas
    c1->Update();
}

void generate_and_plot_points_in_circle() {
    int n = 1000;  // Number of points to generate
    double radius = 1.0;  // Example radius of the circle
    generate_random_points_in_circle(n, radius);  // Generate and plot n random points inside the circle
}

int main() {
    generate_and_plot_points_in_circle();
    return 0;
}