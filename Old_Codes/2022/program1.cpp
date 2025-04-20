//In order to compile the code use .L program1.cpp command
//Then in order to run any of the functions just use their name, for example randomNumberCout_01()

#include<iostream>

using namespace std;

void randomNumberCout_01()
{
    cout << "Give a natural number of random numbers to simulate: ";
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++)
    {
        cout << gRandom->Uniform(0,1) << endl;                                  //Print in the terminal the random number from the uniform distribution from range 0 to 1
    }
}

void randomNumberCout_ab()
{
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

void randomNumberHistogram_01()
{
    TH1D *histogram = new TH1D( "name", "title;X axis;Y axis", 100, 0, 1 );     //Initialization of a histogram with 100 bins in range 0 to 1
    
    cout << "Give a natural number of random numbers to simulate: ";
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++)
    {
        histogram -> Fill( gRandom->Uniform(0,1) );                             //Filling the histogram with the random number from uniform distribution from range 0 to 1
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );                  //Initialization of a canva on which the histogram will be drawn
    histogram -> Draw();                                                        //Plotting of the histogram
}

void randomNumberHistogram_ab()
{
    TH1D *histogram = new TH1D( "name", "title;X axis;Y axis", 100, 0, 1 );
    
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
        histogram -> Fill( gRandom->Uniform(a,b) );
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );
    histogram -> Draw();
}
