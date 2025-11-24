float f(float E){
    return 1.0 - E/340.0;
}

float accept_reject(TRandom3* randGen, float Emax, float fmax){
    while(true){
        float E = randGen->Uniform(0, Emax);
        float y = randGen->Uniform(0, fmax);
        if(y < f(E)){
            return E;
        }
    }
}

void Part1B_Sampling_from_Custom_Distribution() {

    TRandom3 *randGen = new TRandom3(0);

    const int nSamples = 10000;
    const float Emax = 340.0;
    const float fmax = 1.0;

    TH1F *hCustom = new TH1F("hCustom", "Custom Distribution;Energy;Frequency", 100, 0, Emax);

    for(int i = 0; i < nSamples; ++i) {
        float sample = accept_reject(randGen, Emax, fmax);
        hCustom->Fill(sample);
    }

    // hCustom->Scale(1.0 / (hCustom->Integral("width"))); // Normalize to PDF

    TCanvas* c1 = new TCanvas("c1", "Sampling from Custom Distribution", 800, 600);
    hCustom->SetLineColor(kBlue);
    hCustom->SetLineWidth(2);
    hCustom->Draw("HIST");

}