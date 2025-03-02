#include<iostream>

using namespace std;

void randomNumber()
{
    gRandom->SetSeed(0);
    double number = gRandom->Uniform(0,1);
    cout << number << endl;
}


void randomNumber_ab()
{
    gRandom->SetSeed(0);
    double a, b;
    cout << "Set range for random number selection" << endl;
    cout << "Lower:  ";
    cin >> a;
    cout << "Upper:  ";
    cin >> b;
    cout << "Give a natural number of random numbers to simulate: ";
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++)
    {
        cout << gRandom->Uniform(a,b) << endl;                                  //Print in the terminal the random number from the uniform distribution from range a to b
    }
}

void randomNumberHistogram()
{
    TH1D *histogram = new TH1D( "name127", "title123;X 456axis;Y 789axis", 100, 0, 1 );     //Initialization of a histogram with 100 bins in range 0 to 1
    
    cout << "Give a natural number of random numbers to simulate: ";
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++)
    {
        double number = gRandom->Uniform(0,1);
        histogram -> Fill( number );                         //Filling the histogram with the random number from uniform distribution from range 0 to 1
    }
    
    TCanvas *canva = new TCanvas( "name", "title159", 900, 600 );                  //Initialization of a canva on which the histogram will be drawn
    histogram -> Draw();                                                        //Plotting of the histogram
}
