#include<iostream>

using namespace std;

void program7()
{
    TH1D *histogram = new TH1D( "name", "title;X axis;Y axis", 100, 0, 0.01 );     // Histogram initialization
    
    const int size = 1000;                                                         // Number of numbers to simulate
    
    double array[size] = {};                                                        // Array to store simulated numbers
    
    for(int i = 0; i < size; i++)
    {
        array[i] = gRandom->Uniform(0,1);                                           // Filling array with random numbers
    }
    
    sort(array, array+size);                                                        // Here one needs to sort the array in ascending order (one can use functions already defined in c++ libraries)
    
    for(int i = 1; i < size; i++)
    {
        histogram->Fill(array[i]-array[i-1]);                                       // Then one needs to fill previously initialized histogram with differences between neighboring elements in array
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 1200, 600 );                     // Canva initialization
    histogram -> Draw();                                                            // Draw hitogram on canva
}
