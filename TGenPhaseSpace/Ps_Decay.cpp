#include <TGenPhaseSpace.h>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TSystem.h>
#include <TStyle.h>

double angle(const TLorentzVector& gamma1, const TLorentzVector& gamma2) {
    Double_t cosTheta = gamma1.Vect().Dot(gamma2.Vect()) / (gamma1.Vect().Mag() * gamma2.Vect().Mag());
    Double_t theta = TMath::ACos(cosTheta) * 180.0 / TMath::Pi();
    return theta;
}

void PsDecaySimulation() {
    gSystem->Load("libPhysics");

    TCanvas *c = new TCanvas("c", "Positronium Decay", 1000, 800);
    c->Divide(2, 2); // 2x2 pads
    TCanvas *new_c = new TCanvas("new_c", "Energy Correlation in Positronium Decay", 1000, 800);

    //gStyle->SetOptStat(0); // Hide stats box

    //double momentum = 0.0; // Positronium at rest (lab = CM frame)
    double momentum = 0.0; // Ps with momentum (e.g., 0.1 MeV along z)
    TLorentzVector Ps(0.0, 0.0, momentum, sqrt(1.022*1.022 + momentum*momentum)); // E = sqrt(m^2 + p^2)

    // p-Ps (2 photons decay)
    Double_t masses_pPs[2] = {0.0, 0.0};
    TGenPhaseSpace event_pPs;
    if (!event_pPs.SetDecay(Ps, 2, masses_pPs)) {
        std::cout << "Error: p-Ps decay not possible!" << std::endl;
        return;
    }

    TH1D *h_pPs = new TH1D("h_pPs", "p-Ps: Angle Between Photons (deg)", 100, 0, 360);

    for (Int_t n = 0; n < 10000; n++) {
        event_pPs.Generate();
        TLorentzVector *gamma1 = event_pPs.GetDecay(0);
        TLorentzVector *gamma2 = event_pPs.GetDecay(1);
        
        Double_t theta = angle(*gamma1, *gamma2);
        h_pPs->Fill(theta);
    }

    // o-Ps (3 photons decay)
    Double_t masses_oPs[3] = {0.0, 0.0, 0.0};
    TGenPhaseSpace event_oPs;
    if (!event_oPs.SetDecay(Ps, 3, masses_oPs)) {
        std::cout << "Error: o-Ps decay not possible!" << std::endl;
        return;
    }

    TH1D *h_oPs = new TH1D("h_oPs", "o-Ps: Angles Between Gammas (deg)", 100, 0, 180);
    TH1D *h_oPs_Energy = new TH1D("h_oPs_Energy", "o-Ps: Photon Energy Distribution (MeV)", 100, 0, 0.511);
    TH1D *h_oPs_Momentum = new TH1D("h_oPs_Momentum", "o-Ps: Photon Momentum (MeV/c)", 100, 0, 0.511);
    TH2D *h_EnergyCorr = new TH2D("h_EnergyCorr", "E1 vs E2;E1 (MeV);E2 (MeV)", 100, 0, 0.511, 100, 0, 0.511);

    for (Int_t n = 0; n < 10000; n++) {
        event_oPs.Generate();
        TLorentzVector *gamma1 = event_oPs.GetDecay(0);
        TLorentzVector *gamma2 = event_oPs.GetDecay(1);
        TLorentzVector *gamma3 = event_oPs.GetDecay(2);

        TVector3 pTot = gamma1->Vect() + gamma2->Vect() + gamma3->Vect();
        if (pTot.Mag() - momentum > 1e-6) { // Should be ~0
            std::cout << "Momentum not conserved!" << std::endl;
        }
        
        h_oPs->Fill(angle(*gamma1, *gamma2));
        h_oPs->Fill(angle(*gamma2, *gamma3));
        h_oPs->Fill(angle(*gamma3, *gamma1));

        h_oPs_Energy->Fill(gamma1->E());
        h_oPs_Energy->Fill(gamma2->E());
        h_oPs_Energy->Fill(gamma3->E());

        h_oPs_Momentum->Fill(gamma1->P());
        h_oPs_Momentum->Fill(gamma2->P());
        h_oPs_Momentum->Fill(gamma3->P());

        h_EnergyCorr->Fill(gamma1->E(), gamma2->E());
        //h_EnergyCorr->Fill(gamma2->E(), gamma3->E());
        //h_EnergyCorr->Fill(gamma3->E(), gamma1->E());
    }

    c->cd(1); h_pPs->Draw();
    c->cd(2); h_oPs->Draw();
    c->cd(3); h_oPs_Energy->Draw();
    c->cd(4); h_oPs_Momentum->Draw();

    new_c->cd();
    h_EnergyCorr->Draw("COLZ");
}