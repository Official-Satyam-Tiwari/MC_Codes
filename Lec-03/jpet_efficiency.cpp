#include "header.h"

double SimulateDistance(double lambda){
    TRandom3 random;
    random.SetSeed(0);

    double r = random.Uniform(0,1);
    double x = -log(1-r)/lambda;

    return x;
}

double efficiency(){
    TRandom3 random;
    random.SetSeed(0);

    int N_acc = 0;
    int N_steps = 10000;
    double lambda = 0.5; //in cm^-1 //decay constant
    double d = 2; //in cm //detector thickness

    for (int i=0; i<N_steps; ++i){
        double r = SimulateDistance(lambda);
        if (r<d){
            N_acc++;
        }
    }

    double eff = (double)N_acc/N_steps;
    double sd = sqrt(eff/N_steps);

    cout<<"Efficiency: "<<eff<<endl;
    cout<<"Standard Deviation: "<<sd<<endl;

    return eff;
}