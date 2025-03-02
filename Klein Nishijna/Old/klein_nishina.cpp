#include "header.h"

const double m_e_kev = 511.0; // electron mass in keV
const double E_gamma = 511.0; // Incident photon energy in keV

//Function to simulate scattered electron energy
double SimulateElectronEnergy(double E_gamma){
    TRandom3 random;
    random.SetSeed(0);

    double theta = random.Uniform(0,2*M_PI);

    double E_scattered = E_gamma/(1 + E_gamma/m_e_kev*(1 - cos(theta)));

    double E_electron = E_gamma - E_scattered;

    return E_electron;
}

void SimulateAndPlot(){
    const int nSteps = 10000;

    TH1D *h = new TH1D("KN Distribution","Electron Energy",100,0,E_gamma); //100 bins from 0 to E_gamma

    for (int i=0; i<nSteps; ++i){
        double E_electron = SimulateElectronEnergy(E_gamma);
        h->Fill(E_electron);
    }

    TCanvas *c = new TCanvas("c","Energy Distribution",800,600); // 800x600 pixels and window title is Energy Distribution
    h->Draw();
    //c->SaveAs("klein_nishina.png");
}