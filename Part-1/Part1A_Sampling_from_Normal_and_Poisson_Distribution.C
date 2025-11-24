void Part1A_Sampling_from_Normal_and_Poisson_Distribution() {
    
    TRandom3 *randGen = new TRandom3(0);

    const int nSamples = 10000;

    double normalMean = 0.0;
    double normalStdDev = 1.0;
    double poissonMean = 5.0;

    TH1F *hNormal = new TH1F("hNormal", "Normal Distribution;Value;Frequency", 100, -5, 5);
    TH1F *hPoisson = new TH1F("hPoisson", "Poisson Distribution;Value;Frequency", 15, -0.5, 14.5);

    for(int i = 0; i < nSamples; ++i) {
        hNormal->Fill(randGen->Gaus(normalMean, normalStdDev));
        hPoisson->Fill(randGen->Poisson(poissonMean));
    }

    TCanvas *c1 = new TCanvas("c1", "Sampling from Distributions", 1200, 600);
    c1->Divide(2,1);    

    c1->cd(1);
    hNormal->Draw();
    hNormal->Fit("gaus");
    
    c1->cd(2);
    hPoisson->Draw();

    hNormal->SetStats(1);
    hPoisson->SetStats(1);
}