#include <iostream> 

using namespace std;

void calculatePi()
{
    int radius = 1;
    int inCircle = 0;
    int total = pow(10, 2);
    
    for(int i = 0; i < total; i++)
    {
        double x, y;
        x = gRandom->Uniform(-radius, radius);
        y = gRandom->Uniform(-radius, radius);
        if( x*x + y*y < radius*radius )
        {
            inCircle++;
        }
    }
    
    double pi = 4. * (double)inCircle / (double)total;
    double er = 4. * sqrt( (double)inCircle ) / (double)total;
    cout << pi << "\t" << er << endl;
}
