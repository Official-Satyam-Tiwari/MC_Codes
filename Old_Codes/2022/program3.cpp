#include<iostream>

using namespace std;


std::pair<double, double> randomNumberVector_ab(double, double, int);

double mypdf();

std::pair<double, double> randomNumberVector_ab(double a, double b, int n)
{
    std::vector <double> values;
    
    for(int i = 0; i < n; i++)
    {
        values.push_back( gRandom->Uniform(a,b) );
    }
    
    double mean = TMath::Mean( values.begin(), values.end() );
    double sigma = sqrt( TMath::StdDev( values.begin(), values.end() ) );    
    return std::make_pair(mean, sigma);
}

void plotDependence()
{
    TGraphErrors* graph = new TGraphErrors();
    double mean, sigma;
    double a, b;
    cout << "Set range for random number selection" << endl;
    cout << "Lower:  ";
    cin >> a;
    cout << "Upper:  ";
    cin >> b;
    
    for(int i = 0; i < 100; i++)
    {
        std::tie(mean, sigma) = randomNumberVector_ab( a, b, i+1 );
//         cout << mean << "\t" << sigma << endl;
        graph -> SetPoint(i, i+1, mean);
        graph -> SetPointError(i, 0, sigma);
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );
    graph -> SetMarkerStyle(8);
    graph -> Draw("AP");
}

double mypdf()
{
    int flag = 0;
    double a = 5.;
    double x0 = 10.;
    double x, y;
    
    while(flag == 0)
    {
        x = ( gRandom->Uniform(0,1) ) * x0;
        y = ( gRandom->Uniform(0,1) ) * a;
        
        if( y < a * TMath::Exp(-a*x) )
        {
            flag=1;
        }
    }
    return x;
}
