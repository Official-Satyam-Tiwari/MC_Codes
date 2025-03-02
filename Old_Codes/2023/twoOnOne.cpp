#include<iostream>

using namespace std;

void twoOnOne()
{
    TH1D *histogram = new TH1D( "Histogram", ";Sum of 10 random numbers;Events", 100, 0, 10 );
    TH1D *histogram2 = new TH1D( "Histogram", ";Sum of 10 random numbers;Events", 100, 0, 10 );
    
    for(int i = 0; i < 1000000; i++)
    {
        double sum = 0.;
        
        for(int j = 0; j < 10; j++)
        {
            sum += gRandom->Uniform(0,1);
        }
        
        histogram -> Fill( sum );
    }
    
    for(int i = 0; i < 1000000; i++)
    {
        double sum = 0.;
        
        for(int j = 0; j < 2; j++)
        {
            sum += gRandom->Uniform(0,5);
        }
        
        histogram2 -> Fill( sum );
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );
    histogram -> Draw("same");
    histogram2 -> Draw("same");
}
