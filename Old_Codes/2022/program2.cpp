#include <iostream> 

using namespace std;

void sumOfRandomNumbers()
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
