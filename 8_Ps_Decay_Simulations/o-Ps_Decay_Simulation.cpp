#include "TRandom3.h"

void Energies(double &E1, double &E2, double &E3, TRandom3 &professor) {

    double me = 511; // in KeV
    while(true){
        E1 = professor.Uniform(0,me);
        E2 = professor.Uniform(0,me);
        if (E2 > me - E1){
            break;
        }
    }
    E3 = 2*me - E1 - E2;
}

// Theta12 = x + pi/2
// Theta23 = y + pi/2
// Theta31 = pi - x - y
// E2 = E1 sinx + E3 siny => f1 = E2 - E1 sinx - E3 siny
// E1 cosx = E2 cosy => f2 = E1 cosx - E2 cosy
// Using Newton's Raphson method to solve the equations

int Angles(double E1, double E2, double E3, double &theta12, double &theta23, double &theta31) {
    double x = M_PI / 4.0;
    double y = M_PI / 4.0;
    double f1, f2;
    double J11, J12, J21, J22, detJ;
    double dx, dy;
    bool converged = false;

    for (int i = 0; i < 10000; i++) {
        f1 = E2 - E1 * sin(x) - E3 * sin(y);
        f2 = E1 * cos(x) - E2 * cos(y);
        //cout<<f1<<f2<<endl;

        if (fabs(f1) < 1e-6 && fabs(f2) < 1e-6) {
            cout << "Converged after " << i << " iterations." << std::endl;
            converged = true;
            break;
        }

        J11 = E1 * cos(x);   // ∂f1/∂x
        J12 = E3 * cos(y);   // ∂f1/∂y
        J21 = -E1 * sin(x);   // ∂f2/∂x
        J22 = E2 * sin(y);    // ∂f2/∂y

        detJ = J11 * J22 - J12 * J21;

        // Avoid division by zero (singular Jacobian)
        if (fabs(detJ) < 1e-10) {
            cout << "Jacobian is singular. Try a different initial guess." << std::endl;
            break;
        }

        // Solve J * [dx, dy] = -[f1, f2]
        dx = (J22 * f1 - J12 * f2) / detJ;
        dy = (-J21 * f1 + J11 * f2) / detJ;

        x -= dx;
        y -= dy;
    }

    if (!converged) {
        //cout << "Did not converge after 10000 iterations." << std::endl;
        return 1; // Indicate failure to converge
    }

    theta12 = x + M_PI / 2.0;
    theta23 = y + M_PI / 2.0;
    theta31 = M_PI - x - y;

    return 0; // Indicate success
}

void plotting_Energies(){
    TRandom3 professor;
    professor.SetSeed(0);

    double E1, E2, E3;

    TH1F *h1 = new TH1F("h1", "1D Histograms of Es", 100, 0, 600);
    TH2D *h2 = new TH2D("h2", "2D Histograms of Es", 73, 0, 511, 73, 0, 511);

    for(int i = 0; i < 100000; i++){
        Energies(E1, E2, E3, professor);
        h1->Fill(E1);
        //h1->Fill(E2);
        //h1->Fill(E3);

        h2->Fill(E1, E2);
        h2->Fill(E1, E3);
        h2->Fill(E2, E3);
    }
    TCanvas *c1 = new TCanvas("c1", "Energies", 800, 600);
    //h1->Draw();
    h2->Draw();
}

void plotting_angles(){
    double E1, E2, E3;
    double theta12, theta23, theta31;

    TRandom3 professor;
    professor.SetSeed(0);

    TH1F *h1 = new TH1F("h1", "1D Histogram of Angles", 100, 0, M_PI);
    TH2D *h2 = new TH2D("h2", "2D Histogram of Angles", 100, 0, M_PI, 100, 0, M_PI);

    for(int i = 0; i < 100000; i++){
        Energies(E1, E2, E3, professor);
        int fail = Angles(E1, E2, E3, theta12, theta23, theta31);
        if (fail==1) {
            //cout << "Failed to calculate angles." << std::endl;
            continue; // Skip this iteration if angles could not be calculated
        }
       // h1->Fill(theta12);
        //h1->Fill(theta23);
        //h1->Fill(theta31);

        h2->Fill(theta12, theta23);
        //h2->Fill(theta12, theta31);
        //h2->Fill(theta23, theta31);
    }
    TCanvas *c1 = new TCanvas("c1", "Angles", 800, 600);
    //h1->Draw();
    h2->Draw();
}