#include<iostream>

using namespace std;

void sumOfRandomNumbers_5()
{
    gRandom->SetSeed(0);
    TH1D *histogram = new TH1D( "Histogram", ";Sum of 5 random numbers;Events", 100, 0, 5 );
    
    cout << "Give a natural number of random sums to simulate: ";
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        double x,y,z,w,k;
        x = gRandom->Uniform(0,1);
        y = gRandom->Uniform(0,1);
        z = gRandom->Uniform(0,1);
        w = gRandom->Uniform(0,1);
        k = gRandom->Uniform(0,1);
        
        double sum = x+y+z+w+k;
        
        histogram -> Fill( sum );
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );
    histogram -> Fit("gaus");
    histogram -> Draw();
}

void sumOfRandomNumbers_10()
{
    TH1D *histogram = new TH1D( "Histogram", ";Sum of 10 random numbers;Events", 100, 0, 10 );
    
    cout << "Give a natural number of random sums to simulate: ";
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        double sum = 0.;
        
        for(int j = 0; j < 10; j++)
        {
            sum += gRandom->Uniform(0,1);
        }
        
        histogram -> Fill( sum );
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );
    histogram -> Fit("gaus");
    histogram -> Draw();
}



void sumOfRandomNumbers_2()
{
    TH1D *histogram = new TH1D( "Histogram", ";Sum of 2 random numbers;Events", 100, 0, 2 );
    
    cout << "Give a natural number of random sums to simulate: ";
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        double sum = 0.;
        
        for(int j = 0; j < 2; j++)
        {
            sum += gRandom->Uniform(0,1);
        }
        
        histogram -> Fill( sum );
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );
    histogram -> Fit("gaus");
    histogram -> Draw();
}
