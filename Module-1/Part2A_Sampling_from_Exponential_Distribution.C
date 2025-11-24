void Part2A_Sampling_from_Exponential_Distribution() {

    const int num_samples = 1000;
    const double lambda = 0.5;

    TRandom3 *randGen = new TRandom3(0);

    TH1F *hist = new TH1F("hist", "Exponential Distribution Samples;Value;Frequency", 100, 0, 20);

    for (int i = 0; i < num_samples; ++i) {
        double u = randGen->Uniform(0.0, 1.0);
        double x = -log(1 - u) / lambda; // Inverse transform sampling

        hist->Fill(x);
    }

    TCanvas *canvas = new TCanvas("canvas", "Exponential Distribution Sampling", 800, 600);
    hist->Draw();

} 