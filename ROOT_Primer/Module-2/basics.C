void basics(){

	TCanvas *c1 = new TCanvas("c1", "My Analysis", 800, 600);

	// Arguments: ("Internal_Name", "Title; X-Axis; Y-Axis", Bins, Min, Max)
	TH1F *hist = new TH1F("hist", "Invariant Mass; Mass [GeV]; Counts", 100, 0, 10);

	TRandom3 *rand = new TRandom3(0); // 0 is the seed

	for (int i=0; i<10000; i++){
		double mass = rand->Gaus(5.0, 1.0); //Mean = 5 & Sigma = 1
		hist->Fill(mass);
	}

	hist->SetFillColor(kBlue-7);
	hist->Draw();
}
