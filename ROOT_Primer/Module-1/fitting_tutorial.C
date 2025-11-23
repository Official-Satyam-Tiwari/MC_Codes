void fitting_tutorial(){
	
	// Fitting using TF1

	TH1F *hist = new TH1F("hist", "Higgs Mass Search", 100, -200, 200);

	TRandom3 *r = new TRandom3();

	for(int i=0; i<1000; i++){
		hist -> Fill(r->Gaus(125,2));
	}

	TF1 *fitFunc = new TF1("fitFunc","gaus",0,140);

	hist->Fit("fitFunc");

	double mean = fitFunc->GetParameter(1);
	double sigma = fitFunc->GetParameter(2);

	cout << mean;

}
