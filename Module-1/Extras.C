#include <iostream>
#include <cmath>
#include "TH1F.h"
#include "TH3D.h"
#include "TCanvas.h"
#include "TRandom3.h"

// Function to demonstrate the INCORRECT way of sampling points uniformly in a sphere
void Extras() {

    TRandom3 *rand = new TRandom3(0);

    const int nPoints = 2000000; // Increased points for clearer density visualization
    const double R = 1.0; // Radius of the sphere
    double r, theta, phi;

    TCanvas *c1 = new TCanvas("c1", "INCORRECT Sampling of Uniform Points in a Sphere", 1200, 600);
    // 3D Histogram to visualize the spatial density
    TH3D *h3 = new TH3D("h3", "3D Density (INCORRECT Sampling);X;Y;Z", 
                        50, -R, R, 50, -R, R, 50, -R, R);
    
    // 1D Histogram to show the non-uniform density along the Z-axis (polar)
    TH1F *h_z_projection = new TH1F("h_z_projection", 
                                    "Z-Axis Projection (INCORRECT Sampling);Z Coordinate;Frequency", 
                                    100, -R, R);

    // --- INCORRECT SAMPLING LOOP ---
    for (int i = 0; i < nPoints; i++) {
        
        // 1. INCORRECT Radial component: Linearly sampling r over-populates the center
        r = rand->Uniform(0.0, R); 
        
        // 2. INCORRECT Polar component: Linearly sampling theta over-populates the poles (Z= +/- R)
        theta = rand->Uniform(0, M_PI);
        
        // 3. Azimuthal component: Uniform sampling is correct
        phi = rand->Uniform(0, 2 * M_PI);

        // Convert spherical to Cartesian coordinates
        double x = r * sin(theta) * cos(phi);
        double y = r * sin(theta) * sin(phi);
        double z = r * cos(theta);

        h3->Fill(x, y, z);
        h_z_projection->Fill(z);
    }

    // --- Visualization ---
    c1->Divide(2, 1);

    // Left Pad: 3D Visualization
    c1->cd(1);
    h3->SetTitle("3D Density (INCORRECT: Center Over-Populated)");
    // Use COLZ to show the density in 3D bins
    h3->Draw("COLZ"); 

    // Right Pad: Z-Axis Projection
    c1->cd(2);
    h_z_projection->SetTitle("Z-Axis Projection (INCORRECT: Poles Over-Populated)");
    h_z_projection->SetLineColor(kRed);
    h_z_projection->SetLineWidth(2);
    h_z_projection->Draw("HIST");

    // Add text explaining the expected distribution for comparison
    TText *expected = new TText(0.5, 0.9, "For UNIFORM density, the Z-projection should be flat.");
    expected->SetNDC();
    expected->SetTextSize(0.04);
    expected->SetTextColor(kBlue);
    expected->Draw();

    c1->Update();
    std::cout << "\n--- INCORRECT Sampling Result ---\n";
    std::cout << "The Z-projection plot (right) shows peaks near Z=1 and Z=-1 (the poles),\n";
    std::cout << "confirming that the linear sampling of theta incorrectly clusters points there.\n";
    std::cout << "The 3D view (left) would also show points clustered near the center.\n";

    // Clean up random generator
    delete rand;
}
