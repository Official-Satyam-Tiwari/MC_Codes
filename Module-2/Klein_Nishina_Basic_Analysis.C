double scattered_energy(double initial_energy, double scatter_angle) {
    const double electron_rest_mass = 511.0; // in keV
    double energy_ratio = 1 + (initial_energy / electron_rest_mass) * (1 - cos(scatter_angle));
    return initial_energy / energy_ratio;
}

double differential_cross_section(double initial_energy, double scatter_angle) {
    const double r0 = 2.818e-15; // classical electron radius in m
    double scattered_E = scattered_energy(initial_energy, scatter_angle);
    double ratio = scattered_E / initial_energy;
    double term1 = ratio * ratio;
    double term2 = ratio + (1 / ratio) - sin(scatter_angle) * sin(scatter_angle);
    return 0.5 * r0 * r0 * term1 * term2;
}

double total_cross_section(double initial_energy) {
    const int num_steps = 1000;
    double total_cs = 0.0;
    double dtheta = M_PI / num_steps;

    for (int i = 0; i < num_steps; ++i) {
        double theta = i * dtheta + dtheta / 2; // Midpoint
        double dcs = differential_cross_section(initial_energy, theta);
        total_cs += dcs * sin(theta) * dtheta; // Integrate over solid angle
    }

    return 2 * M_PI * total_cs; // Multiply by 2π for azimuthal symmetry
}

double accept_reject_sampling(double initial_energy, TRandom3* rand) {
    const double max_dcs = differential_cross_section(initial_energy, 0); // Max at 0 degrees
    double scatter_angle, f, f_scatter_angle;

    while (true) {
        scatter_angle = rand->Uniform(0, M_PI); // Random angle between 0 and π
        f_scatter_angle = differential_cross_section(initial_energy, scatter_angle);
        f = rand->Uniform(0, max_dcs);
        if (f < f_scatter_angle) {
            return scatter_angle;
        }
    }

    return scatter_angle;
}

void Klein_Nishina_Basic_Analysis() {
    const double initial_energy = 511.0; // in keV
    TRandom3 *rand = new TRandom3(0);

    double total_cs = total_cross_section(initial_energy);
    std::cout << "Total Cross Section: " << total_cs << " m^2" << std::endl;

    const int num_samples = 10000;

    TH1D *h_scatter_angle = new TH1D("h_scatter_angle", "Scattering Angle Distribution;Angle (rad);Counts", 100, 0, M_PI);

    for (int i = 0; i < num_samples; ++i) {
        double angle = accept_reject_sampling(initial_energy, rand);
        double scattered_E = scattered_energy(initial_energy, angle);
        
        h_scatter_angle->Fill(angle);
    }

    TCanvas *c1 = new TCanvas("c1", "Klein-Nishina Scattering", 800, 600);
    h_scatter_angle->Draw();
}