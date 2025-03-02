#include <TGenPhaseSpace.h>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TRandom3.h>

double angle(const TLorentzVector& gamma1, const TLorentzVector& gamma2) {
    Double_t cosTheta = gamma1.Vect().Dot(gamma2.Vect()) / (gamma1.Vect().Mag() * gamma2.Vect().Mag());
    Double_t theta = TMath::ACos(cosTheta) * 180.0 / TMath::Pi();
    return theta;
}

void PsDecayInTissue() {
    gSystem->Load("libPhysics");
    TRandom3 rand(0);

    TCanvas *c = new TCanvas("c", "Ps Decay", 1200, 800);
    c->Divide(2, 2);

    TLorentzVector Ps(0.0, 0.0, 0.1, sqrt(1.022 * 1.022 + 0.1 * 0.1)); // E = sqrt(m^2 + p^2) //0.1 MeV momentum // Simulating the thermal motion in the tissues

    TH1D *h_pPs_angle = new TH1D("h_pPs_angle", "p-Ps: Photon Angle (deg)", 100, 0, 360);
    TH1D *h_oPs_angle = new TH1D("h_oPs_angle", "o-Ps: Gamma1-Gamma2 Angle (deg)", 100, 0, 180);
    TH1D *h_oPs_energy = new TH1D("h_oPs_energy", "o-Ps: Photon Energy (MeV)", 100, 0, 1.1);
    TH1D *h_ratio = new TH1D("h_ratio", "o-Ps: 3gamma/2gamma Ratio per Event", 100, 0, 0.03);

    // p-Ps (2 photons)
    Double_t masses_pPs[2] = {0.0, 0.0};
    TGenPhaseSpace event_pPs;
    event_pPs.SetDecay(Ps, 2, masses_pPs);

    // o-Ps (3 photons)
    Double_t masses_oPs[3] = {0.0, 0.0, 0.0};
    TGenPhaseSpace event_oPs;
    event_oPs.SetDecay(Ps, 3, masses_oPs);

    int nEvents = 10000;
    int oPs_3gamma_count = 0, oPs_2gamma_count = 0;

    for (Int_t n = 0; n < nEvents; n++) {
        // p-Ps decay
        event_pPs.Generate();
        TLorentzVector *g1_pPs = event_pPs.GetDecay(0);
        TLorentzVector *g2_pPs = event_pPs.GetDecay(1);
        h_pPs_angle->Fill(angle(*g1_pPs, *g2_pPs));

        // o-Ps decay
        event_oPs.Generate();
        TLorentzVector *g1_oPs = event_oPs.GetDecay(0);
        TLorentzVector *g2_oPs = event_oPs.GetDecay(1);
        TLorentzVector *g3_oPs = event_oPs.GetDecay(2);

        h_oPs_angle->Fill(angle(*g1_oPs, *g2_oPs));
        h_oPs_energy->Fill(g1_oPs->Energy());

        // Simulate o-Ps 3γ vs 2γ (pick-off annihilation)
        // In tissue, ~98% of o-Ps converts to 2γ due to pick-off (simplified model)
        Double_t prob_2gamma = 0.98; // Pick-off probability
        if (rand.Uniform() < prob_2gamma) {
            oPs_2gamma_count++;
        } else {
            oPs_3gamma_count++;
        }
        if (oPs_2gamma_count > 0) {
            h_ratio->Fill((double)oPs_3gamma_count / (oPs_2gamma_count + oPs_3gamma_count));
        }
    }

    c->cd(1); h_pPs_angle->Draw();
    c->cd(2); h_oPs_angle->Draw();
    c->cd(3); h_oPs_energy->Draw();
    c->cd(4); h_ratio->Draw();
}