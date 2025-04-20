#include <TRandom3.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <iostream>
#include <cmath>

// Function to calculate the probability of a match (all pairs checked)
double prob_bd(int n) {
    if (n <= 1) return 0.0; // No chance of a match for 1 or fewer people

    TRandom3 random;
    random.SetSeed(0);

    int n_steps = 10000; // Number of simulations
    int fav = 0; // Number of favorable outcomes

    for (int i = 0; i < n_steps; ++i) {
        // Generate birthdays
        int bd[n];
        for (int j = 0; j < n; ++j) {
            bd[j] = static_cast<int>(random.Uniform(0, 365)); // Generate a day [0, 364]
        }

        // Check all pairs for a match
        bool match_found = false;
        for (int j = 0; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (bd[j] == bd[k]) {
                    match_found = true;
                    break;
                }
            }
            if (match_found) break;
        }

        if (match_found) {
            fav++;
        }
    }

    // Calculate and return the probability
    return static_cast<double>(fav) / n_steps;
}

// Function to plot probability vs. n
void plot_prob_vs_n() {
    const int n_max = 100; // Maximum number of people
    double prob[n_max];    // Store probabilities
    double x[n_max];       // Store x-axis values (number of people)

    // Calculate probabilities for different values of n
    for (int i = 1; i <= n_max; ++i) {
        x[i - 1] = i; // Store n values starting from 1
        prob[i - 1] = prob_bd(i);
    }

    // Create a canvas and TGraph for plotting
    TCanvas* c1 = new TCanvas("c1", "Probability vs. n", 800, 600);
    TGraph* graph = new TGraph(n_max, x, prob);

    // Customize the graph
    graph->SetTitle("Probability of Birthday Match vs. Number of People");
    graph->GetXaxis()->SetTitle("Number of People (n)");
    graph->GetYaxis()->SetTitle("Probability");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.8);
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(2);

    // Draw the graph
    graph->Draw("ALP");

    // Save the canvas
    c1->SaveAs("prob_vs_n_corrected.png");
}