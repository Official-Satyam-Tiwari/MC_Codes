#include "header.h"

double SimulateDistance(double lambda){
    TRandom3 random;
    random.SetSeed(0);

    double r = random.Uniform(0,1);
    double x = -log(1-r)/lambda;

    return x;
}

void SimulateAndPlot(){
    const int nSteps = 10000;
    const double lambda = 0.1;

    TH1D *h = new TH1D("Exponential Distribution","Distance",100,0,100); //100 bins from 0 to 10

    for (int i=0; i<nSteps; ++i){
        double x = SimulateDistance(lambda);
        h->Fill(x);
        cout << x << endl;
    }

    TCanvas *c = new TCanvas("c","Distance Distribution",800,600); // 800x600 pixels and window title is Distance Distribution
    h->Draw();
}