#include<iostream>

using namespace std;

void detectorResponse()
{
    TH1D *histogram1 = new TH1D( "1st annihilation photon", ";Energy [keV];Events", 15000, 0, 1500 );
    
    for(int i = 0; i < 100000; i++)
    {
        double number = 511 + gRandom->Gaus(0,20);
        histogram1 -> Fill( number );
    }
    
    TH1D *histogram2 = new TH1D( "2nd annihilation photon", ";Energy [keV];Events", 15000, 0, 1500 );
    
    for(int i = 0; i < 100000; i++)
    {
        double number = 511 + gRandom->Gaus(0,20);
        histogram2 -> Fill( number );
    }
    
    TH1D *histogram3 = new TH1D( "Prompt photon", ";Energy [keV];Events", 15000, 0, 1500 );
    
    for(int i = 0; i < 100000; i++)
    {
        double number = 1270 + gRandom->Gaus(0,20);
        histogram3 -> Fill( number );
    }
    
    TCanvas *canva = new TCanvas( "c", "c", 900, 600 );
    gStyle->SetOptStat(0);
    histogram1 -> Draw("same");
    histogram2 -> Draw("same");
    histogram3 -> Draw("same");
}
