void analyze() {
    // 1. Open the file we made in Module 3
    TFile *file = new TFile("../Module-3/experiment_data.root", "READ");
    
    // 2. Get the Tree (The Table)
    TTree *tree = (TTree*)file->Get("DataTree");

    // 3. Create variables to hold the data
    double energy;
    int nParticles;

    // 4. Connect the Tree Branches to our variables
    // This tells ROOT: "When I load a row, put the data here."
    tree->SetBranchAddress("energy", &energy);
    tree->SetBranchAddress("nParticles", &nParticles);

    // 5. Create Histograms to compare results
    // Hist 1: All Energy
    TH1F *h_all = new TH1F("h_all", "All Events", 50, 0, 100);
    
    // Hist 2: Only "High Multiplicity" events (nParticles > 2)
    TH1F *h_cut = new TH1F("h_cut", "High Multiplicity Only", 50, 0, 100);
    h_cut->SetLineColor(kRed); // Make the cut plot Red

    // 6. The Analysis Loop
    int nEntries = tree->GetEntries(); // Get total rows
    
    for (int i = 0; i < nEntries; i++) {
        tree->GetEntry(i); // Load row 'i' into memory
        
        // Always fill the "All" histogram
        h_all->Fill(energy);
        
        // --- THE FILTER (CUT) ---
        // Only keep events with more than 2 particles
        if (nParticles > 2) {
            h_cut->Fill(energy);
        }
    }

    // 7. Draw both on the same canvas to compare
    TCanvas *c1 = new TCanvas();
    h_all->Draw();       // Draw the Black line (All)
    h_cut->Draw("SAME"); // Draw Red line ON TOP of the Black one
    
    // Add a Legend so we know which is which
    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9); // Coordinates (x1, y1, x2, y2)
    leg->AddEntry(h_all, "All Events", "l");
    leg->AddEntry(h_cut, "nParticles > 2", "l");
    leg->Draw();
}
