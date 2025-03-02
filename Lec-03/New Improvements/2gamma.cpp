#include "header.h"
#include <TGraph.h>

//const double E_thresh = 200.0; //in keV
const double m_e_kev = 511.0; // electron mass in keV
const double E_gamma = 511.0; // Incident photon energy in keV

double SimulateDistance(double lambda){
    TRandom3 random;
    random.SetSeed(0);

    double r = random.Uniform(0,1);
    double x = -log(1-r)/lambda;

    return x;
}

double SimulateElectronEnergy(double E_gamma){
    TRandom3 random;
    random.SetSeed(0);

    double theta = random.Uniform(0,2*M_PI);

    double E_scattered = E_gamma/(1 + E_gamma/m_e_kev*(1 - cos(theta)));

    double E_electron = E_gamma - E_scattered;

    return E_electron;
}

double efficiency(double E_thresh){
    TRandom3 random;
    random.SetSeed(0);

    int N_acc = 0;
    int N_steps = 10000;
    double lambda = 0.5; //in cm^-1 //decay constant
    double d = 2; //in cm //detector thickness

    for (int i=0; i<N_steps; ++i){
        double r1 = SimulateDistance(lambda);
        double r2 = SimulateDistance(lambda);
        if (r1<d && r2<d){
            double E_electron1 = SimulateElectronEnergy(E_gamma);
            double E_electron2 = SimulateElectronEnergy(E_gamma);
            if (E_electron1>=E_thresh && E_electron2>=E_thresh){
                N_acc++;
            }
        }
    }

    double eff = (double)N_acc/N_steps;
    double sd = sqrt(eff/N_steps);

    //cout<<"Efficiency: "<<eff<<endl;
    //cout<<"Standard Deviation: "<<sd<<endl;
    return eff;
}

void EfficiencyVsEthresh() {
    const int nPoints = 500;
    double E_thresh = 0.0;

    TGraph *graph = new TGraph();
    graph->SetTitle("Efficiency vs Energy Threshold;Energy Threshold (keV);Efficiency");

    for (int i = 0; i < nPoints; ++i) {
        double eff = efficiency(E_thresh);
        graph->SetPoint(i, E_thresh, eff);
        E_thresh += 1.0;
    }

    TCanvas *c1 = new TCanvas("c1", "Efficiency vs Energy Threshold", 800, 600);
    graph->Draw("AL");
    //c1->SaveAs("EfficiencyVsEthresh.png"); // Save the plot
}