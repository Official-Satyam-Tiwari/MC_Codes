//#include "TSystem.h"
#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"
#include "TH1D.h"

void basic(){
    //gSystem->Load("libPhysics");

    TLorentzVector target(0,0,0,0.938); // Proton at rest
    TLorentzVector beam(0,0,0.4,0.4);   // Photon with energy 0.4 GeV
    TLorentzVector W = beam + target;   // Total system 4-momentum

    double masses[2] = { 0.938, 0.135 }; // Mass of proton and pion (GeV)

    TGenPhaseSpace event;
    event.SetDecay(W,2,masses); // Define 2-body decay

    TH1D *h = new TH1D("his", "Theta Distribution", 100, 0, 180);

    for(int n = 0; n < 100000; n++){
        event.Generate();
        TLorentzVector *pProton = event.GetDecay(0);
        TLorentzVector *pPi0 = event.GetDecay(1);
        
        h->Fill(pPi0->Theta() * 57.3); // Convert rad to degrees
    }

    h->Draw();
}