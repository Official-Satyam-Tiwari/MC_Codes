#include<iostream>

using namespace std;

double giform()
{
    gRandom->SetSeed(0);
    
    double x, y;
    
    int flag = 0;
    
    double A = 100;
    double gmax = 1;
    
    while(flag == 0)
    {
        x = gRandom->Uniform(-A,A);
        y = gRandom->Uniform(0,1) * gmax;
        
        if( y < TMath::Exp(-x*x) )
        {
            flag=1;
        }
    }
    return x;
}

void my_randomNumber()
{
    TH1D *histogram = new TH1D( "Histogram", "Exponential distribution;;Events", 100, -10, 10 );
    
    cout << "Give a natural number of random numbers to simulate: ";
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        double value;
        value = giform();
        histogram -> Fill( value );
    }
    
    TCanvas *canva = new TCanvas( "name", "Canva", 900, 600 );
    histogram -> Fit("gaus");
    histogram -> Draw();
}
