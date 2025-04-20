#include <iostream>
#include <TRandom3.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TMath.h>

using namespace std;

int best_candidate(int n = 100) {
    TRandom3 random;
    random.SetSeed(0);

    int ranks[n];

    // Randomly assign ranks to candidates
    for (int i = 0; i < n; i++) {
        ranks[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int j = random.Integer(n);
        int temp = ranks[i];
        ranks[i] = ranks[j];
        ranks[j] = temp;
    }

    // Find the minimum rank or the best candidate
    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (ranks[i] < ranks[min_index]) {
            min_index = i;
        }
    }

    // Find the minimum rank till n/e
    int sample_size = n / TMath::E(); // Dynamic threshold based on n
    //int sample_size = n*0.7;
    int min_till_sample = 100000;

    for (int i = 0; i < sample_size; i++) {
        if (ranks[i] < min_till_sample) {
            min_till_sample = ranks[i];
        }
    }

    // Find the first candidate better than min_till_sample
    for (int i = sample_size; i < n; i++) {
        if (ranks[i] < min_till_sample) {
            return (ranks[i] == 0); // Success if best candidate found because rank 0 is the best
        }
    }

    return 0; // Failure
}

double probability(int n = 100) {
    int n_steps = 10000;
    int count = 0;
    for (int i = 0; i < n_steps; i++) {
        count += best_candidate(n);
    }
    return static_cast<double>(count) / n_steps;
}

void plot_n_vs_probability() {
    const int max_n = 100;
    TGraph *g = new TGraph(max_n);
    for (int i = 1; i <= max_n; i++) {
        g->SetPoint(i - 1, i, probability(i));
    }

    TCanvas *c = new TCanvas("c", "Probability vs n", 800, 600);
    g->SetTitle("Probability of Selecting the Best Partner;Number of Lovers (n);Probability");
    g->SetMarkerStyle(20);
    g->SetLineColor(kBlue);
    g->SetLineWidth(2);
    g->Draw("APL");
    c->Draw();
}