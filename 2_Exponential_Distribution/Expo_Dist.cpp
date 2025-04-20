#include <TRandom3.h>
#include <iostream>
#include <cmath>
#include <TGraph.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <vector>

using namespace std;

double simulate_exponential_distribution() {
    double tau = 1e-5; // mean lifetime

    TRandom3 random;
    random.SetSeed(0);

    double t = -tau * log(1 - random.Uniform(0, 1));
    return t;
}

void plot_expo_dist() {
    int N = 10000; // Number of events
    vector<double> t(N);

    for (int i = 0; i < N; i++) {
        t[i] = simulate_exponential_distribution();
    }

    TCanvas *c1 = new TCanvas("c1", "Exponential Distribution", 800, 600);
    TH1D *h1 = new TH1D("h1", "Exponential Distribution;Time (t);Frequency", 100, 0, 1e-3);

    for (int i = 0; i < N; i++) {
        h1->Fill(t[i]);
    }

    h1->Draw();

    // Fit original distribution
    TF1 *expoFit = new TF1("expoFit", "[0]*exp(-x/[1])", 0, 1e-3);
    expoFit->SetParameters(1000, 1e-5); // Initial guesses
    h1->Fit("expoFit");
    expoFit->Draw("SAME");

    // Memoryless property demonstration
    double t1 = 2 * 1e-5; // Cutoff time
    TH1D *h2 = new TH1D("h2", "Memoryless Property;Time after Cutoff (t-t1);Frequency", 100, 0, 1e-3);

    for (int i = 0; i < N; i++) {
        if (t[i] > t1) {
            h2->Fill(t[i] - t1); // Shifted times
        }
    }

    TCanvas *c2 = new TCanvas("c2", "Memoryless Property", 800, 600);
    h2->Draw();

    TF1 *memorylessFit = new TF1("memorylessFit", "[0]*exp(-x/[1])", 0, 1e-3);
    memorylessFit->SetParameters(1000, 1e-5);
    h2->Fit("memorylessFit");
    memorylessFit->Draw("SAME");
}