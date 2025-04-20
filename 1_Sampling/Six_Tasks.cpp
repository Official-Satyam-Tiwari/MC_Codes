#include <TRandom3.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>

// Function to generate random numbers from a normal distribution
void generate_normal_distribution() {
    const int N = 10000; // Number of samples
    TRandom3 random;
    random.SetSeed(0);

    TH1D *h_norm = new TH1D("h_norm", "Normal Distribution;Value;Frequency", 100, -5, 5);
    for (int i = 0; i < N; i++) {
        double value = random.Gaus(0, 1); // Mean = 0, Sigma = 1
        h_norm->Fill(value);
    }

    TCanvas *c1 = new TCanvas("c1", "Normal Distribution", 800, 600);
    h_norm->Draw();
}

// Function to generate random numbers for a given distribution
void generate_random_distribution() {
    const int N = 1000000; // Number of samples
    TRandom3 random;
    random.SetSeed(0);

    // Define the target distribution f(E) = 1 - E/340
    auto f = [](double E) { return 1 - E / 340.0; };
    const double E_max = 340;
    const double f_max = 1; // Maximum value of f(E)

    TH1D *h_energy = new TH1D("h_energy", "Custom Distribution;Energy (E);Frequency", 100, 0, 340);

    for (int i = 0; i < N; i++) {
        double E, f_rand;
        do {
            E = random.Uniform(0, E_max);
            f_rand = random.Uniform(0, f_max);
        } while (f_rand >= f(E)); //It will come out of loop when f_rand < f(E) i.e. the point is under the curve

        h_energy->Fill(E);
    }

    TCanvas *c2 = new TCanvas("c2", "Custom Distribution", 800, 600);
    h_energy->Draw();
}

// Function to plot Poisson distribution
void plot_poisson_distribution() {
    const int N = 1000000; // Number of samples
    TRandom3 random;
    random.SetSeed(0);

    const double mean = 5; // Poisson mean
    TH1D *h_poisson = new TH1D("h_poisson", "Poisson Distribution;Value;Frequency", 20, 0, 20);

    for (int i = 0; i < N; i++) {
        int value = random.Poisson(mean);
        h_poisson->Fill(value);
    }

    TCanvas *c3 = new TCanvas("c3", "Poisson Distribution", 800, 600);
    h_poisson->Draw();
}

// Function to verify the Central Limit Theorem (CLT) using Poisson distribution
void verify_clt_poisson() {
    const int N = 10000; // Number of samples
    const int k = 10;    // Number of variables to sum
    TRandom3 random;
    random.SetSeed(0);

    const double mean = 5; // Poisson mean
    TH1D *h_clt = new TH1D("h_clt", "CLT Verification with Poisson;Sum of Variables;Frequency", 100, 0, 100);

    for (int i = 0; i < N; i++) {
        double sum = 0;
        for (int j = 0; j < k; j++) {
            sum += random.Poisson(mean);
        }
        h_clt->Fill(sum);
    }

    TCanvas *c4 = new TCanvas("c4", "CLT Verification with Poisson", 800, 600);
    h_clt->Draw();
}

// Function to verify the Central Limit Theorem (CLT) using Exponential distribution
void verify_clt_exponential() {
    const int N = 10000; // Number of samples
    const int k = 20;    // Number of variables to sum
    TRandom3 random;
    random.SetSeed(0);

    const double tau = 1; // Mean lifetime for exponential distribution
    TH1D *h_clt_exp = new TH1D("h_clt_exp", "CLT Verification with Exponential;Sum of Variables;Frequency", 100, 0, 40);

    for (int i = 0; i < N; i++) {
        double sum = 0;
        for (int j = 0; j < k; j++) {
            sum += random.Exp(tau);
        }
        h_clt_exp->Fill(sum);
    }

    TCanvas *c5 = new TCanvas("c5", "CLT Verification with Exponential", 800, 600);
    h_clt_exp->Draw();
}

// Main function to call all the tasks
void lec_01_tasks() {
    generate_normal_distribution();
    generate_random_distribution();
    plot_poisson_distribution();
    verify_clt_poisson();
    verify_clt_exponential();
}