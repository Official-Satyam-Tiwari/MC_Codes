void weird_mc(){

	// Generating data that follows the theory

	TF1 *myTheory = new TF1("theory", "x*x*exp(-x)", 0, 10);

	TH1F *hist = new TH1F("h","MC from Theory", 100, 0, 10);

	for(int i=0; i<10000; i++){
		double random_var = myTheory->GetRandom();
		hist->Fill(random_var);
	}

	hist->Draw();
}
