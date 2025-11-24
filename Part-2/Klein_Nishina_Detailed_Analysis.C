double scattered_energy(double initial_energy, double scatter_angle) {
    const double electron_rest_mass = 511.0; // keV
    double energy_ratio = 1 + (initial_energy / electron_rest_mass) * (1 - cos(scatter_angle));
    return initial_energy / energy_ratio;
}

double differential_cross_section(double initial_energy, double scatter_angle) {
    const double r0 = 2.818e-15; // m
    double E_scat = scattered_energy(initial_energy, scatter_angle);
    double ratio = E_scat / initial_energy;
    double term1 = ratio * ratio;
    double term2 = ratio + (1.0 / ratio) - sin(scatter_angle) * sin(scatter_angle);
    return 0.5 * r0 * r0 * term1 * term2; // m^2 / sr
}

double total_cross_section(double initial_energy) {
    const int num_steps = 1000;
    double total_cs = 0.0;
    double dtheta = M_PI / num_steps;

    for (int i = 0; i < num_steps; ++i) {
        double theta = i * dtheta + dtheta / 2;
        double dcs = differential_cross_section(initial_energy, theta);
        total_cs += dcs * sin(theta) * dtheta;
    }
    return 2.0 * M_PI * total_cs;
}

double accept_reject_sampling(double initial_energy, TRandom3* rand) {
    const double max_dcs = differential_cross_section(initial_energy, 0.0);
    while (true) {
        double theta = rand->Uniform(0, M_PI);
        double f = rand->Uniform(0, max_dcs);
        double f_theta = differential_cross_section(initial_energy, theta);
        if (f < f_theta) return theta;
    }
}

void Klein_Nishina_Detailed_Analysis() {
    const double initial_energy = 511.0; // keV
    TRandom3 *rand = new TRandom3(0);
    const int num_samples = 10000;

    double total_cs = total_cross_section(initial_energy);
    std::cout << "Total Cross Section: " << total_cs << " m^2" << std::endl;

    TH1D *h_angle = new TH1D("h_angle", "Scattering Angle Distribution;Angle (rad);Counts", 100, 0, M_PI);
    TH1D *h_energy = new TH1D("h_energy", "Scattered Photon Energy;Energy (keV);Counts", 100, 0, initial_energy);
    TH2D *h_angle_energy = new TH2D("h_angle_energy", "Energy vs Angle;Angle (rad);Energy (keV)", 100, 0, M_PI, 100, 0, initial_energy);

    for (int i = 0; i < num_samples; ++i) {
        double theta = accept_reject_sampling(initial_energy, rand);
        double E_scat = scattered_energy(initial_energy, theta);
        h_angle->Fill(theta);
        h_energy->Fill(E_scat);
        h_angle_energy->Fill(theta, E_scat);
    }

    // Analytical differential cross section vs angle
    TGraph *g_dcs = new TGraph();
    for (int i = 0; i <= 100; ++i) {
        double theta = i * M_PI / 100.0;
        double dcs = differential_cross_section(initial_energy, theta);
        g_dcs->SetPoint(i, theta, dcs);
    }

    TCanvas *c1 = new TCanvas("c1", "Klein-Nishina Analysis", 1200, 800);
    c1->Divide(2,2);

    c1->cd(1);
    h_angle->Draw();

    c1->cd(2);
    h_energy->Draw();

    c1->cd(3);
    g_dcs->SetTitle("Differential Cross Section;Angle (rad);dσ/dΩ (m^{2}/sr)");
    g_dcs->Draw("AL");

    c1->cd(4);
    h_angle_energy->Draw("COLZ");

    c1->Update();
}