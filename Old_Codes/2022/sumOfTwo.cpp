#include<iostream>

using namespace std;

void sumOfTwo()
{
    TH1D *histogram1 = new TH1D( "x1", ";x1;Counts", 100, 0, 1 );          //Initialization of a histogram with 100 bins in range 0 to 1
    TH1D *histogram2 = new TH1D( "x2", ";x2;Counts", 100, 0, 1 );          //Initialization of a histogram with 100 bins in range 0 to 1
    TH1D *histogram3 = new TH1D( "x1+x2", ";x1+x2;Counts", 200, 0, 2 );    //Initialization of a histogram with 200 bins in range 0 to 2
    
    for(int i = 0; i < pow(10,6); i++)
    {
        double x1, x2;
        x1 = gRandom->Uniform(0, 1);
        x2 = gRandom->Uniform(0, 1);
        histogram1 -> Fill( x1 );
        histogram2 -> Fill( x2 );   
        histogram3 -> Fill( x1+x2 );   
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 1800, 600 );             //Initialization of a canva on which the histogram will be drawn
    canva->Divide(3,1);                                                     //Divide canva into multiple sub-canvas
    canva->cd(1);                                                           //Move to 1st sub-canva
    histogram1 -> GetYaxis() -> SetRangeUser(0,20000);                      //Set range of histogram on Y axis
    histogram1 -> Draw();
    canva->cd(2);                                                           //Move to 2st sub-canva
    histogram2 -> Draw();
    canva->cd(3);                                                           //Move to 3st sub-canva
    histogram3 -> Draw();
}
