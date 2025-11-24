void Part1C_Generating_Uniform_Points_in_a_Sphere() {

    TRandom3 *rand = new TRandom3(0);

    const int nPoints = 1000000;
    double r, theta, phi;

    TCanvas *c1 = new TCanvas("c1", "Uniform Points in a Sphere", 800, 800);
    TH3D *h3 = new TH3D("h3", "Uniform Points in a Sphere;X;Y;Z", 100, -1, 1, 100, -1, 1, 100, -1, 1);
    
    for (int i = 0; i < nPoints; i++) {
        r = cbrt(rand->Uniform(0, 1));       
        theta = acos(1 - 2 * rand->Uniform(0, 1)); 
        // r = rand->Uniform(0, 1); // Original incorrect method
        // theta = rand->Uniform(0, M_PI); // Original incorrect method
        phi = rand->Uniform(0, 2 * M_PI);

        double x = r * sin(theta) * cos(phi);
        double y = r * sin(theta) * sin(phi);
        double z = r * cos(theta);

        h3->Fill(x, y, z);
    }

    h3->Draw("BOX");
    c1->Update();
}