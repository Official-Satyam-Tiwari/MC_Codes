#include<iostream>

using namespace std;

double mypdf();

void randomNumber_PDF()
{
    TH1D *histogram = new TH1D( "Histogram", "Exponential distribution;;Events", 100, 0, 10 );
    
    cout << "Give a natural number of random numbers to simulate: ";
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        double value;
        value = mypdf();
        histogram -> Fill( value );
    }
    
    TCanvas *canva = new TCanvas( "name", "Canva", 900, 600 );
    histogram -> Draw("HIST");
}

double mypdf()
{
    int flag = 0;
    double tau = 1.;
    double xMax = 10.;
    double x, y;
    
    while(flag == 0)
    {
        x = ( gRandom->Uniform(0,1) ) * xMax;
        y = ( gRandom->Uniform(0,1) ) * tau;
        
        if( y < TMath::Exp(-x/tau) )
        {
            flag=1;
        }
    }
    return x;
}
