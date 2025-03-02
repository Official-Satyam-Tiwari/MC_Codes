#include<iostream>

using namespace std;

double timeDistribution();

void program8()
{
    TH1D *histogram1 = new TH1D( "name", "1st order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram2 = new TH1D( "name", "2nd order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram3 = new TH1D( "name", "3rd order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram4 = new TH1D( "name", "4th order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram5 = new TH1D( "name", "5th order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram6 = new TH1D( "name", "6th order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram7 = new TH1D( "name", "7th order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram8 = new TH1D( "name", "8th order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram9 = new TH1D( "name", "9th order;X axis;Y axis", 100, -2, 2 );
    TH1D *histogram10 = new TH1D( "name", "10th order;X axis;Y axis", 100, -2, 2 );
    
    const int numberOpticalperSide = 10;
    const int numberAnnihilationperSide = 100000;
    
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
        
        histogram1->Fill(rightPMT[0]-leftPMT[0]);
        histogram2->Fill(rightPMT[1]-leftPMT[1]);
        histogram3->Fill(rightPMT[2]-leftPMT[2]);
        histogram4->Fill(rightPMT[3]-leftPMT[3]);
        histogram5->Fill(rightPMT[4]-leftPMT[4]);
        histogram6->Fill(rightPMT[5]-leftPMT[5]);
        histogram7->Fill(rightPMT[6]-leftPMT[6]);
        histogram8->Fill(rightPMT[7]-leftPMT[7]);
        histogram9->Fill(rightPMT[8]-leftPMT[8]);
        histogram10->Fill(rightPMT[9]-leftPMT[9]);
        
    }
    
    TCanvas *canva = new TCanvas( "name", "Canva", 1200, 600 );
    canva->Divide(5,2);
    canva->cd(1);
    histogram1 -> Draw("HIST");
    canva->cd(2);
    histogram2 -> Draw("HIST");
    canva->cd(3);
    histogram3 -> Draw("HIST");
    canva->cd(4);
    histogram4 -> Draw("HIST");
    canva->cd(5);
    histogram5 -> Draw("HIST");
    canva->cd(6);
    histogram6 -> Draw("HIST");
    canva->cd(7);
    histogram7 -> Draw("HIST");
    canva->cd(8);
    histogram8 -> Draw("HIST");
    canva->cd(9);
    histogram9 -> Draw("HIST");
    canva->cd(10);
    histogram10 -> Draw("HIST");
    
    cout << histogram1 -> GetStdDev() << endl;
    cout << histogram2 -> GetStdDev() << endl;
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
