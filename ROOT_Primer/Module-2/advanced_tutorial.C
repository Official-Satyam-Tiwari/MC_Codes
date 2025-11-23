void advanced_tutorial() {
    // 1. Setup the Stage (Canvas)
    TCanvas *c1 = new TCanvas("c1", "Distributions", 1000, 500);
    c1->Divide(2, 1); // Split into 2 pads
    
    // 2. Setup the Containers (Histograms)
    // Hist 1: Gaussian (Standard Signal)
    TH1F *h_sig = new TH1F("h_sig", "Signal (Gaussian);Mass;Events", 50, 0, 20);
    h_sig->SetLineColor(kBlue);
    h_sig->SetFillColor(kAzure-9); // Faint blue fill
    
    // Hist 2: Exponential (Background Decay)
    TH1F *h_bkg = new TH1F("h_bkg", "Background (Decay);Time;Events", 50, 0, 10);
    h_bkg->SetLineColor(kRed);
    h_bkg->SetLineWidth(3);
    
    // 3. The Engine
    TRandom3 *gen = new TRandom3(0);
    
    // 4. Simulation Loop
    for(int i=0; i<10000; i++) {
        h_sig->Fill( gen->Gaus(10, 2) ); // Mean 10, Sigma 2
        h_bkg->Fill( gen->Exp(2.0) );    // Mean Lifetime 2.0
    }
    
    // 5. Drawing Pad 1 (Linear Scale)
    c1->cd(1);
    h_sig->Draw();
    
    // 6. Drawing Pad 2 (Log Scale - Crucial for Exp decay)
    c1->cd(2);
    gPad->SetLogy(); // Turn on Log Scale for Y-axis
    h_bkg->Draw();
    
    // 7. Save
    c1->SaveAs("tutorial_plot.png");
}
