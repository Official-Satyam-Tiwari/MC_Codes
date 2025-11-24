void Part1C_Generating_Uniform_Points_in_a_Circle() {

    TRandom3 *rand = new TRandom3(0);

    const int nPoints = 1000000;
    double r, theta;

    TCanvas *c1 = new TCanvas("c1", "Uniform Points in a Circle", 800, 800);
    TH2D *h2 = new TH2D("h2", "Uniform Points in a Circle;X;Y", 100, -1, 1, 100, -1, 1);
    
    for (int i = 0; i < nPoints; i++) {
        r = sqrt(rand->Uniform(0, 1)); // Corrected for uniform distribution in circle
        //r = rand->Uniform(0, 1); // Original incorrect method
        theta = rand->Uniform(0, 2 * M_PI);

        double x = r * cos(theta);
        double y = r * sin(theta);

        h2->Fill(x, y);
    }

    h2->Draw("COLZ");
    c1->Update();

}