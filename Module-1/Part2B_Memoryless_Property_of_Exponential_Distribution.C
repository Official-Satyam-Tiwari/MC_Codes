void Part2B_Memoryless_Property_of_Exponential_Distribution() {

    const int num_trials = 1000;
    const double lambda = 0.5;
    const double t = 2.0; // Time already waited

    TRandom3 *randGen = new TRandom3(0);

    TH1F *hist_memoryless = new TH1F("hist_memoryless", "Memoryless Property;Value;Frequency", 100, 0, 20);
    TH1F *hist_standard = new TH1F("hist_standard", "Standard Exponential;Value;Frequency", 100, 0, 20);

    for (int i = 0; i < num_trials; ++i) {
        double u1 = randGen->Uniform(0.0, 1.0);
        double x_memoryless = t + (-log(1 - u1) / lambda); // Memoryless property

        hist_memoryless->Fill(x_memoryless);

        double u2 = randGen->Uniform(0.0, 1.0);
        double x_standard = -log(1 - u2) / lambda;

        hist_standard->Fill(x_standard);
    }

    TCanvas *canvas = new TCanvas("canvas_memoryless", "Memoryless Property of Exponential Distribution", 1200, 600);
    canvas->Divide(2,1);

    canvas->cd(1);
    hist_memoryless->SetTitle("Waiting Time Given Already Waited t");
    hist_memoryless->Draw();

    canvas->cd(2);
    hist_standard->SetTitle("Standard Exponential Waiting Time");
    hist_standard->Draw();
}