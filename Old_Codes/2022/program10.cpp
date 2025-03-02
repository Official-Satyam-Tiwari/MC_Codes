#include<iostream>

using namespace std;

double timeDistribution();

void program10()
{
    
    const int numberOpticalperSide = 10;
    const int numberAnnihilationperSide = 1000;
    
    std::vector <double> difference[numberOpticalperSide];
    
    TGraph* graph = new TGraph();
    
    for(int j = 0; j < numberAnnihilationperSide; j++)
    {
        
        double rightPMT[numberOpticalperSide] = {};
        double leftPMT[numberOpticalperSide] = {};
        
        for(int i = 0; i < numberOpticalperSide; i++)
        {
            rightPMT[i] = timeDistribution();
            leftPMT[i] = timeDistribution();
        }
        
        sort(rightPMT, rightPMT+numberOpticalperSide);
        sort(leftPMT, leftPMT+numberOpticalperSide);
        
        for(int k = 0; k < numberOpticalperSide; k++)
        {
            difference[k].push_back(rightPMT[k]-leftPMT[k]);
        }
        
    }
    
    for(int i = 0; i < numberOpticalperSide; i++)
    {
//         cout << TMath::StdDev( difference[i].begin(), difference[i].end() ) << endl;
        graph -> SetPoint(i, i+1, TMath::StdDev( difference[i].begin(), difference[i].end() ));
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 600 );
    graph -> SetTitle("Std Dev of ith order statistic;Order;Std Dev");
    graph -> SetMarkerStyle(8);
    graph -> Draw("AP");
}

double timeDistribution()
{
    int flag = 0;
    double sigma = 1.;
    double x, y;
    
    while(flag == 0)
    {
        x = ( gRandom->Uniform(-2,2) );
        y = ( gRandom->Uniform(0,1) );
        
        if( y < TMath::Exp( - x*x / (2*sigma*sigma) ) )
        {
            flag=1;
        }
    }
    return x;
}
