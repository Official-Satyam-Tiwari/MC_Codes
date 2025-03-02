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

void WrapAngle(double& angle) {
    angle = fmod(angle, 2 * M_PI); // Wrap to [0, 2π)
    if (angle < 0) {
        angle += 2 * M_PI;
    }
}

void CalculateModuleAngles(int n, double b, double r0, std::vector<double>& phi_min, std::vector<double>& phi_max) {
    double delta_phi = 2 * M_PI / n; // Angular spacing between module centers
    double delta = atan(0.5 * b / r0); // Angular half-width of a module

    phi_min.clear();
    phi_max.clear();

    for (int i = 0; i < n; ++i) {
        double phi_center = i * delta_phi;
        double phi_min_i = phi_center - delta;
        double phi_max_i = phi_center + delta;

        WrapAngle(phi_min_i); // Ensure angle is in [0, 2π)
        WrapAngle(phi_max_i);

        /*double temp;
        if (phi_min_i > phi_max_i) {
            temp = phi_min_i;
            phi_min_i = phi_max_i;
            phi_max_i = temp;
        }*/

        phi_min.push_back(phi_min_i);
        phi_max.push_back(phi_max_i);
    }
}



double complex_efficiency(){
    double b = 10.00; //in cm
    double d = 2.00; //in cm
    double r0 = 40.00; //in cm

    const double c = atan(0.5*b/r0);

    double phi_1_max = c;
    double phi_1_min = 2*M_PI-c;

    //double phi_1_min = c;
    //double phi_1_max = 2*M_PI - c;

    double phi_2_max = M_PI/2 + c;
    double phi_2_min = M_PI/2 - c;

    double phi_3_max = M_PI + c;
    double phi_3_min = M_PI - c;

    double phi_4_max = 3*M_PI/2 + c;
    double phi_4_min = 3*M_PI/2 - c;

    //cout<<"Original Phis: "<<phi_1_max<<" "<<phi_1_min<<" "<<phi_2_max<<" "<<phi_2_min<<" "<<phi_3_max<<" "<<phi_3_min<<" "<<phi_4_max<<" "<<phi_4_min<<endl;

    int n = 4; // Number of modules
    std::vector<double> phi_min_check;
    std::vector<double> phi_max_check;

    CalculateModuleAngles(n, b, r0, phi_min_check, phi_max_check);

    /*cout<<"Calculated Phis: ";
    for (int i = 0; i < n; ++i) {
        cout<<phi_max_check[i]<<" "<<phi_min_check[i]<<" ";
    }
    cout<<endl;*/

    int N_acc = 0;
    int N_steps = 1000;
    const double lambda = 0.5; //in cm^-1 //Absorption coefficient of the detector

    for(int i=0; i<N_steps; ++i){
        TRandom3 random;
        random.SetSeed(0);

        double phi = random.Uniform(0,M_PI*2);

        double chi = fmod(phi + M_PI, 2 * M_PI);

        //double chi = random.Uniform(0,M_PI*2);

    if (
        ((phi_1_min < phi && phi < phi_1_max) || 
        (phi_2_min < phi && phi < phi_2_max) || 
        (phi_3_min < phi && phi < phi_3_max) || 
        (phi_4_min < phi && phi < phi_4_max)) && 
        ((phi_1_min < chi && chi < phi_1_max) || 
        (phi_2_min < chi && chi < phi_2_max) || 
        (phi_3_min < chi && chi < phi_3_max) || 
        (phi_4_min < chi && chi < phi_4_max)) 
        && (fabs(chi - phi) - M_PI) < 1e-6) // Ensure chi and phi are exactly 180° apart
    {
        double r1 = SimulateDistance(lambda);
        double r2 = SimulateDistance(lambda);
        if (r1 * cos(phi) < d and r2*cos(chi) < d) {
            N_acc++;
        }
    }

    }
    double efficiency = (double)N_acc/N_steps;
    //cout<<"Efficiency: "<<efficiency<<endl;
    return efficiency;
}

double complex_efficiency_n_detectors(int n) {
    double b = 10.00; // in cm
    double d = 2.00; // in cm
    double r0 = 40.00; // in cm

    // Calculate module angular ranges dynamically
    std::vector<double> phi_min;
    std::vector<double> phi_max;
    CalculateModuleAngles(n, b, r0, phi_min, phi_max);

    /*cout << "Calculated Phis (Min, Max): ";
    for (int i = 0; i < n; ++i) {
        cout << "(" << phi_min[i] << ", " << phi_max[i] << ") ";
    }
    cout << endl;*/

    int N_acc = 0;
    int N_steps = 1000;
    const double lambda = 0.5; // in cm^-1 (Absorption coefficient of the detector)

    TRandom3 random;
    random.SetSeed(0);

    for (int i = 0; i < N_steps; ++i) {
        double phi = random.Uniform(0, 2 * M_PI);
        double chi = random.Uniform(0, 2 * M_PI);

        bool phi_in_range = false;
        bool chi_in_range = false;

        // Check if phi and chi are within any detector's range
        for (int j = 0; j < n; ++j) {
            if (phi_min[j] < phi && phi < phi_max[j]) {
                phi_in_range = true;
    
            }
            if (phi_min[j] < chi && chi < phi_max[j]) {
                chi_in_range = true;
            }
        }

        bool scout = (fabs(chi - phi) - M_PI) < 1e-6; // Ensure chi and phi are exactly 180° apart

        // Check if phi and chi satisfy all conditions
        if (phi_in_range && chi_in_range && scout) {
            double r = SimulateDistance(lambda);
            if (r * cos(phi) < d) {
                N_acc++;
            }
        }
    }

    double efficiency = (double)N_acc / N_steps;
    return efficiency;
}

void Eff_hist(){
    TH1D *h = new TH1D("Efficiency Distribution","B2B Efficiency",1000,0,0.2); //100 bins from 0 to 1

    for(int i=0; i<1000; ++i){
        double eff = complex_efficiency();
        h->Fill(eff);
    }

    TCanvas *c = new TCanvas("c","Efficiency Distribution",800,600); // 800x600 pixels and window title is Efficiency Distribution
    h->Draw();
}

void EfficiencyVsDetectors() {
    double r0 = 40.00; // in cm
    double b = 10.00; // in cm
    int max_detectors = (2*M_PI*r0/b);
    max_detectors = 100;
    cout<<"Max Detectors: "<<max_detectors<<endl;
    double detectors[max_detectors];
    double efficiencies[max_detectors];

    for (int n = 1; n <= max_detectors; ++n) {
        detectors[n - 1] = n;
        efficiencies[n - 1] = complex_efficiency_n_detectors(n);
        cout << "Efficiency for " << n << " detectors: " << efficiencies[n - 1] << endl;
    }


    TGraph* graph = new TGraph(max_detectors, detectors, efficiencies);
    graph->SetTitle("Efficiency vs Number of Detectors;Number of Detectors;Efficiency");
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);
    graph->SetLineWidth(2);
    graph->SetLineColor(kRed);

    // Plot the graph
    TCanvas* canvas = new TCanvas("canvas", "Efficiency vs Number of Detectors", 800, 600);
    graph->Draw("APL");
    //canvas->SaveAs("EfficiencyVsDetectors.png");
}
