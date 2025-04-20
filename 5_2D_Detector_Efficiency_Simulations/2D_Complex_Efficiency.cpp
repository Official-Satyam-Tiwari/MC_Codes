#include "header.h"
#include <TGraph.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>

const double m_e_kev = 511.0; // electron mass in keV
const double E_gamma = 511.0; // Incident photon energy in keV

double SimulateDistance(double lambda){ // Inverse transform sampling for exponential distribution
    TRandom3 random;
    random.SetSeed(0);

    double r = random.Uniform(0,1);
    double x = -log(1-r)/lambda;

    return x;
}

// Klein-Nishina formula
double KleinNishina(double E, double theta) {
    const double re = 2.817e-13; // Classical electron radius in cm
    const double mec2 = 0.511;   // Electron rest energy in MeV
    double cosTheta = TMath::Cos(theta);
    double E_prime = E / (1 + (E / mec2) * (1 - cosTheta));
    double ratio = E_prime / E;
    return 0.5 * re * re * ratio * ratio * (ratio + 1 / ratio - TMath::Sin(theta) * TMath::Sin(theta));
}

double simulateTheta(double E_gamma){ //Using Klein Nishina Formula
    TRandom3 random;
    random.SetSeed(0);

    double accepted_theta;
    
    double f_max = KleinNishina(E_gamma, 0); // Maximum value of the Klein-Nishina formula at theta = 0
     
    bool accepted = false;

    while (!accepted) {
        double theta = random.Uniform(0, TMath::Pi()); // Scattering angle in radians
        double f = random.Uniform(0, f_max);
        double f_theta = KleinNishina(E_gamma, theta);

        if (f < f_theta) {
            accepted = true;
            accepted_theta = theta;
            break;
        }
    }

    return accepted_theta;

}

void plotThetaHistogram(double E_gamma, int n_samples) {
    TH1F *hist = new TH1F("theta_hist", "Theta Distribution;Theta (radians);Counts", 100, 0, 2*TMath::Pi());

    for (int i = 0; i < n_samples; ++i) {
        double theta = simulateTheta(E_gamma);
        hist->Fill(theta);
    }

    TCanvas *canvas = new TCanvas("canvas", "Theta Distribution", 800, 600);
    hist->Draw();
    //canvas->SaveAs("theta_distribution.png");
}

double SimulateElectronEnergy(double E_gamma){
    TRandom3 random;
    random.SetSeed(0);

    double theta = simulateTheta(E_gamma) ;// do using klein nishina formula

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

    //cout<<"Efficiency: "<<eff<<endl;
    //cout<<"Standard Deviation: "<<sd<<endl;``
    return eff;
}

void EfficiencyVsEthresh() {
    const int nPoints = 350;
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

double finding_angle(double phi,double phi1,double phi2,double phi3,double phi4, bool det1, bool det2, bool det3, bool det4){
    if (det1 == true) {
        return phi1 - phi;
    } else if (det2) {
        return phi2 - phi;
    } else if (det3) {
        return phi3 - phi;
    } else if (det4) {
        return phi4 - phi;
    }
    return 0.0; // Default return value if none of the conditions are met
}

double complex_efficiency(){
    double b = 10.00; //in cm
    double d = 2.00; //in cm
    double r0 = 40.00; //in cm

    const double c = atan(0.5*b/r0);

    double phi1 = 0.0;
    double phi2 = M_PI/2;
    double phi3 = M_PI;
    double phi4 = 3*M_PI/2;

    double phi_1_max = c;
    double phi_1_min = 2*M_PI - c;

    double phi_2_max = M_PI/2 + c;
    double phi_2_min = M_PI/2 - c;

    double phi_3_max = M_PI + c;
    double phi_3_min = M_PI - c;

    double phi_4_max = 3*M_PI/2 + c;
    double phi_4_min = 3*M_PI/2 - c;

    int N_acc = 0;
    int N_steps = 100000;
    const double lambda = 0.5; //in cm^-1 //Absorption coefficient of the detector

    for(int i=0; i<N_steps; ++i){
        TRandom3 random;
        random.SetSeed(0);

        double phi = random.Uniform(0,2*M_PI);

        bool det1 = (phi_1_min<phi || phi<phi_1_max);
        bool det2 = (phi_2_min<phi && phi<phi_2_max);
        bool det3 = (phi_3_min<phi && phi<phi_3_max);
        bool det4 = (phi_4_min<phi && phi<phi_4_max);

        if(det1 || det2 || det3 || det4){
            double r = SimulateDistance(lambda);
            double angle = finding_angle(phi, phi1, phi2, phi3, phi4, det1, det2, det3, det4);
            if(r*cos(angle)<d){
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

    for(int i=0; i<100; ++i){
        double eff = complex_efficiency();
        h->Fill(eff);
    }

    TCanvas *c = new TCanvas("c","Efficiency Distribution",800,600); // 800x600 pixels and window title is Efficiency Distribution
    h->Draw();
}

