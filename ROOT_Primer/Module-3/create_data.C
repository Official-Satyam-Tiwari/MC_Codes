void create_data() {
    // 1. Open a FILE to write into ("RECREATE" overwrites old files)
    TFile *file = new TFile("experiment_data.root", "RECREATE");

    // 2. Create the TREE (tree name, description)
    TTree *tree = new TTree("DataTree", "My Simulation Data");

    // 3. Define variables (The containers)
    double energy;
    int nParticles;

    // 4. Create BRANCHES (Connect variables to the Tree)
    // Note the "&" (Address of). The Tree needs to know WHERE the variable lives.
    tree->Branch("energy", &energy, "energy/D");      // D = Double
    tree->Branch("nParticles", &nParticles, "nParticles/I"); // I = Integer

    // 5. Fill the Tree
    TRandom3 *r = new TRandom3();
    
    for (int i = 0; i < 100000; i++) {
        // Simulate data
        energy = r->Uniform(1, 1000); 
        nParticles = r->Integer(100); // 0 to 99 particles

        // Save this "Row"
        tree->Fill();
    }

    // 6. Save and Close
    tree->Write();
    file->Close();
    
    std::cout << "File 'experiment_data.root' created!" << std::endl;
}
