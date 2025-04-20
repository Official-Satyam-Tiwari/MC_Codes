#include "TRandom3.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TMath.h"
#include <cmath>

// Generate three photon energies from o-Ps decay
void Energies(double &E1, double &E2, double &E3, TRandom3 &professor) {
    double me = 511; // in keV
    while (true) {
        E1 = professor.Uniform(0, me);
        E2 = professor.Uniform(0, me);
        if (E2 > me - E1) break;
    }
    E3 = 2 * me - E1 - E2;
}

// Compute angles using momentum conservation (cosine law approx)
bool Angles(double E1, double E2, double E3, double &theta12, double &theta23, double &theta31) {
    double arg12 = (E3*E3 - E1*E1 - E2*E2) / (2*E1*E2);
    double arg23 = (E1*E1 - E2*E2 - E3*E3) / (2*E2*E3);
    double arg31 = (E2*E2 - E1*E1 - E3*E3) / (2*E3*E1);

    theta12 = acos(arg12);
    theta23 = acos(arg23);
    theta31 = acos(arg31);

    return false;  // success
}

// Weight using matrix element formula
double Weight(double E1, double E2, double E3, double me) {
    if (E1 == 0 || E2 == 0 || E3 == 0) return 0;

    double term1 = pow((me - E1) / (E2 * E3), 2);
    double term2 = pow((me - E2) / (E1 * E3), 2);
    double term3 = pow((me - E3) / (E1 * E2), 2);
    return term1 + term2 + term3;
}

// Plot energies with weights
void plotting_Energies() {
    TRandom3 professor;
    professor.SetSeed(0);

    double E1, E2, E3;
    double me = 511;

    TH2D *h2 = new TH2D("h2", "2D Histogram of Energies (Weighted);E_i [keV];E_j [keV]", 73, 0, 511, 73, 0, 511);

    for (int i = 0; i < 100000; i++) {
        Energies(E1, E2, E3, professor);
        double w = Weight(E1, E2, E3, me);

        h2->Fill(E1, E2, w);
        //h2->Fill(E1, E3, w);
        //h2->Fill(E2, E3, w);
    }

    TCanvas *c1 = new TCanvas("c1", "Weighted Energies", 800, 600);
    h2->Draw("COLZ");
}

// Plot angles with weights
void plotting_angles() {
    double E1, E2, E3;
    double theta12, theta23, theta31;
    double me = 511;

    TRandom3 professor;
    professor.SetSeed(0);

    TH2D *h2 = new TH2D("h2", "2D Histogram of Angles (Weighted);#theta_{12} [rad];#theta_{23} [rad]", 100, 0, M_PI, 100, 0, M_PI);

    for (int i = 0; i < 100000;i++) {
        Energies(E1, E2, E3, professor);
        if (Angles(E1, E2, E3, theta12, theta23, theta31)) continue;

        double w = Weight(E1, E2, E3, me);
        h2->Fill(theta12, theta23, w);
    }

    TCanvas *c2 = new TCanvas("c2", "Weighted Angles", 800, 600);
    h2->Draw("COLZ");
}