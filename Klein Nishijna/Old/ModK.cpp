
void klein_nishina() 
 {
    double r_0 = 2.82e-13; 
    double m_e_c2 = 511; 
    double E0 = 511.0;
    double E_thrs = 342;
    
    TH1F *hist_511 = new TH1F("hist_511", "Energy Distribution of Scattered Electrons; Energy (keV); Counts", 1000, 0, 1300);
    TH1F *hist_1275 = new TH1F("hist_1275", "Energy Distribution of Scattered Electrons; Energy (keV); Counts", 1000, 0, 1300);

    int n;
    cout << "Enter the number of events to simulate : ";
    cin >> n;

    for (int i = 1; i <= n; i++) 
     {   
       double phi = gRandom->Uniform(0, 360);
       double E_gamma_511 = 511 / (1 + (511 / m_e_c2) * (1 - cos(phi)));
       double E_511 = (511 - E_gamma_511) ;
       hist_511->Fill(E_511);           

       double E_gamma_1275 = 1275 / (1 + (1275 / m_e_c2) * (1 - cos(phi)));
       double E_1275 = (1275 - E_gamma_1275) ;
       hist_1275->Fill(E_1275);
        
        // double cross_section = (pow(r_0, 2) / 2.0) * pow(E_gamma_511 / E0, 2) * ((E0 / E_gamma_511) + (E_gamma_511 / E0) - pow(sin(phi), 2));    
     }
     
    /*    
       int nBins = hist_1275->GetNbinsX();
    for (int i = 1; i <= nBins; i++) 
     {
       hist_1275->SetBinContent(i, hist_1275->GetBinContent(i) * 0.1); 
     }
    */
   
     TCanvas *canvas = new TCanvas("canvas", "Energy Distribution of Scattered Electrons", 800, 600);
    
     hist_1275->Draw(); 
     hist_511->Draw("SAME");
     
     double minY_1275 = hist_1275->GetMinimum();
     double maxY_511 = hist_511->GetMaximum();
  //   hist_1275->SetMinimum(minY_1275);
 //    hist_1275->SetMaximum(maxY_511);
     
     hist_1275->SetLineColor(kRed);
     hist_511->SetLineColor(kBlue); 
}
