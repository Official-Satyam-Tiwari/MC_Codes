#include<iostream>

using namespace std;

void program6()
{
    TH1D *histogram = new TH1D( "name", "title;X axis;Y axis", 100, 0, 0.001 );     // Histogram initialization
    
    const int size = 10000;                                                         // Number of numbers to simulate
    
    double array[size] = {};                                                        // Array to store simulated numbers
    
    for(int i = 0; i < size; i++)
    {
        array[i] = gRandom->Uniform(0,1);                                           // Filling array with random numbers
    }
    
    SortingAlgorithm(array);                                                        // Here one needs to sort the array in ascending order (one can use functions already defined in c++ libraries)
    
    for( /*this for loop may be needed*/ )
    {
        histogram->Fill( nextElement - Element );                                   // Then one needs to fill previously initialized histogram with differences between neighboring elements in array
    }
    
    TCanvas *canva = new TCanvas( "name", "title", 1200, 600 );                     // Canva initialization
    histogram -> Draw();                                                            // Draw hitogram on canva
}
