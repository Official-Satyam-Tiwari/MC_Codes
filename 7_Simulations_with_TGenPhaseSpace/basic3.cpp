#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"
#include "TVector3.h"
#include "TH1D.h"

void basic(){
    TLorentzVector beam(0.0, 0.0, 0.611, 1.138);
    TLorentzVector target(0.0, 0.0, 0.0, 1.8756);
    TLorentzVector W = beam + target;

    Double_t masses[3] = {0.938, 0.938, 0.9396}; // p, p, n

    TGenPhaseSpace event;
    event.SetDecay(W, 3, masses); // 3-body decay  

    TCanvas *c1 = new TCanvas("c1", "Angles", 800, 400);
    c1->Divide(2, 1); // Two pads: lab and CM

    TH1D *hLab = new TH1D("hLab", "Neutron Theta (Lab)", 100, 0, 180);
    TH1D *hCM = new TH1D("hCM", "Neutron Theta (CM)", 100, 0, 180);

    for (Int_t n = 0; n < 100000; n++) {
        event.Generate();
        TLorentzVector *pNeutron = event.GetDecay(2); // Neutron is the third particle

        // Lab frame angle
        hLab->Fill(pNeutron->Theta() * 57.3); // Convert to degrees

        // CM frame: Boost neutron to CM frame
        TVector3 boost = W.BoostVector(); // Boost vector of initial system
        TLorentzVector pNeutronCM = *pNeutron; //creates a copy
        pNeutronCM.Boost(-boost); // Inverse boost to CM frame
        hCM->Fill(pNeutronCM.Theta() * 57.3);
        }

    c1->cd(1); hLab->Draw();
    c1->cd(2); hCM->Draw();
}