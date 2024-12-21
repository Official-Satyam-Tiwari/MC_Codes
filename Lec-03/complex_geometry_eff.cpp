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
        double r = SimulateDistance(lambda);
        if (r<d){
            double E_electron = SimulateElectronEnergy(E_gamma);
            if (E_electron>=E_thresh){
                N_acc++;
            }
        }
    }

    double eff = (double)N_acc/N_steps;
    double sd = sqrt(eff/N_steps);

    cout<<"Efficiency: "<<eff<<endl;
    //cout<<"Standard Deviation: "<<sd<<endl;
    return eff;
}

void EfficiencyVsEthresh() {
    const int nPoints = 300;
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

double complex_efficiency(){
    double b = 10.00; //in cm
    double d = 2.00; //in cm
    double r0 = 40.00; //in cm

    const double c = atan(0.5*b/r0);

    double phi_1_max = c;
    double phi_1_min = 2*M_PI - c;

    double phi_2_max = M_PI/2 + c;
    double phi_2_min = M_PI/2 - c;

    double phi_3_max = M_PI + c;
    double phi_3_min = M_PI - c;

    double phi_4_max = 3*M_PI/2 + c;
    double phi_4_min = 3*M_PI/2 - c;

    int N_acc = 0;
    int N_steps = 1000;
    const double lambda = 0.5; //in cm^-1 //Absorption coefficient of the detector

    for(int i=0; i<N_steps; ++i){
        TRandom3 random;
        random.SetSeed(0);

        double phi = random.Uniform(0,2*M_PI);
        if((phi_1_min<phi && phi<phi_1_max) || (phi_2_min<phi && phi<phi_2_max) || (phi_3_min<phi && phi<phi_3_max) || (phi_4_min<phi && phi<phi_4_max)){
            double r = SimulateDistance(lambda);
            if(r*cos(phi)<d){
                N_acc++;
            }
        }
    }
    double efficiency = (double)N_acc/N_steps;
    //cout<<"Efficiency: "<<efficiency<<endl;
    return efficiency;
}

void Eff_hist(){
    TH1D *h = new TH1D("Efficiency Distribution","Efficiency",1000,0,0.2); //100 bins from 0 to 1

    for(int i=0; i<1000; ++i){
        double eff = complex_efficiency();
        h->Fill(eff);
    }

    TCanvas *c = new TCanvas("c","Efficiency Distribution",800,600); // 800x600 pixels and window title is Efficiency Distribution
    h->Draw();
}

