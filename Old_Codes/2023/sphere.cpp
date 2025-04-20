#include<iostream>

using namespace std;

void simSphere()
{
    TH3D *histogram = new TH3D( "", ";x;y;z", 100, -2, 2, 100, -2, 2, 100, -2, 2 );
    
    for(int i = 0; i < 100000; i++)
    {
        double phi, cosTheta, r;
//         r = 1;
        r = pow(gRandom->Uniform(0,1) , 1./3.);
        phi = gRandom->Uniform(0,360);
        phi = phi/360.*2.*TMath::Pi();
        cosTheta = gRandom->Uniform(-1,1);
        
        double x, y, z;
        double theta = acos(cosTheta);
//         double theta = gRandom->Uniform(0,180);
//         theta = theta/360.*2.*TMath::Pi();
        x = r * sin(theta) * cos(phi);
        y = r * sin(theta) * sin(phi);
        z = r * cos(theta);
        
        histogram -> Fill( x, y, z );
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 900 );
    histogram -> Draw();
}

void simCircle()
{
    TH2D *histogram = new TH2D( "", ";x;y", 100, -2, 2, 100, -2, 2 );
    
    for(int i = 0; i < 100000; i++)
    {
        double phi, r;
        r = sqrt(gRandom->Uniform(0,1));
        phi = gRandom->Uniform(0,360);
        phi = phi/360.*2.*TMath::Pi();
        
        double x, y;
        x = r * cos(phi);
        y = r * sin(phi);
        
        histogram -> Fill( x, y );
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 900, 900 );
    histogram -> Draw("colz");
}
