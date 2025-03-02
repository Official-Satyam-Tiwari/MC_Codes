#include<iostream>

using namespace std;

void sensitivity()
{
    int N = 100;
    int Nacc = 0;
    float phiMin = 45.;
    float phiMax = 180. - phiMin;
    float d =   //scintillator thickness
    float mu =  //attenuation coefficient
    
    for(int i = 0; i < N; i++)
    {
        float phi = gRandom->Uniform(0,1)*TMath::Pi();
        if(phi > phiMin && phi < phiMax)
            float real_d = d*sin(phi);      //or cosine
            if(gRandom->Uniform(0,1) < 1-TMath::Exp(-mu*real_d))
            {
                Nacc++;
            }
    }
    
    cout << "Sensitivity: " << (float)N/(float)Nacc << endl;
}
