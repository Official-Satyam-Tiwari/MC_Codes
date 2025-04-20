#include <TRandom3.h>
#include <TMath.h>
#include <TH1F.h>
#include <iostream>

const double kElectronRestEnergy = 0.511; // MeV
const double kClassicalElectronRadius = 2.817e-13; // cm

double SimulateDistance(double lambda) {
    static TRandom3 random;
    return -log(random.Uniform()) / lambda;
}

double KleinNishina(double E, double theta) {
    double cosTheta = cos(theta);
    double E_prime = E / (1 + (E/kElectronRestEnergy)*(1 - cosTheta));
    double ratio = E_prime/E;
    return 0.5 * kClassicalElectronRadius*kClassicalElectronRadius * ratio*ratio * (ratio + 1/ratio - sin(theta)*sin(theta));
}

double simulateTheta(double E_gamma) {
    static TRandom3 random;
    double theta, f_theta;
    double f_max = KleinNishina(E_gamma, 0);
    
    do {
        //theta = random.Uniform(0, TMath::Pi());
        theta = acos(random.Uniform(-1, 1)); // Uniformly sample theta in [0, π]

        f_theta = KleinNishina(E_gamma, theta);
    } while (f_theta < random.Uniform(0, f_max));
    
    return theta;
}

bool check_angle_4sides(double angle, double acceptance_angle, double& detector_angle) {
    // Normalize angle to [0, 2π) just for safety
    angle = fmod(angle, 2*M_PI);
    if (angle < 0) angle += 2*M_PI;

    if (angle >= 2*M_PI-acceptance_angle || angle < acceptance_angle) {
        detector_angle = 0.0;
        return true;
    }

    else if (angle >= M_PI/2 - acceptance_angle && angle < M_PI/2 + acceptance_angle) {
        detector_angle = M_PI/2;
        return true;
    }

    else if (angle >= M_PI - acceptance_angle && angle < M_PI + acceptance_angle) {
        detector_angle = M_PI;
        return true;
    }

    else if (angle >= 3*M_PI/2 - acceptance_angle && angle < 3*M_PI/2 + acceptance_angle) {
        detector_angle = 3*M_PI/2;
        return true;
    }

    detector_angle = 99999.9; // Default value when not detected
    return false;
}
   
double efficiency(double E_gamma = 0.511, int N_steps = 100000) {
    TRandom3 random;
    random.SetSeed(0);

    double lambda = 0.5;   // cm^-1 (total interaction coefficient)
    
    double detector_thickness = 2.0;  // cm
    double detector_width = 10.0;     // cm
    double detector_radius = 10.0;    // cm
    double acceptance_angle = atan(0.5*detector_width/detector_radius);

    int N_total = N_steps;
    int N_detected = 0;               // Total detected photons
    int N_detected_scattered_same = 0;  // Scattered in same detector
    int N_detected_scattered_other = 0; // Scattered to other detector
    int N_undetected = 0;              // Never detected photons

    for (int i = 0; i < N_total; ++i) {

        double distance = SimulateDistance(lambda);
        double phi = random.Uniform(0, 2*TMath::Pi());
        double first_detector_angle;
        
        // Check if initial photon hits any detector
        bool initially_detected = check_angle_4sides(phi, acceptance_angle, first_detector_angle) && 
                                (fabs(distance * cos(phi - first_detector_angle)) < detector_thickness);
        
        if (initially_detected) {
            N_detected++;
            
            // Simulate Compton scattering
            double theta = simulateTheta(E_gamma);
            double scattered_phi = fmod(phi + theta, 2*TMath::Pi());
            double scatter_distance = SimulateDistance(lambda);
            
            // Check if scattered in same detector
            double path_in_same = scatter_distance * fabs(cos(scattered_phi - first_detector_angle));
            double total_path_same = fabs(distance * cos(phi - first_detector_angle)) + path_in_same;
            
            if (total_path_same < detector_thickness) {
                N_detected_scattered_same++;
            } 
            else {
                // Check if scattered to other detector
                double second_detector_angle;
                bool hits_other = check_angle_4sides(scattered_phi, acceptance_angle, second_detector_angle);
                
                if (hits_other) {
                    double path_in_other = scatter_distance * fabs(cos(scattered_phi - second_detector_angle));
                    if (path_in_other < detector_thickness) {
                        N_detected_scattered_other++;
                    }
                }
            }
        } 
        else {
            N_undetected++;
        }
    }

    int N_detected_unscattered = N_detected - N_detected_scattered_same - N_detected_scattered_other;
    cout<<N_detected_unscattered<<endl;

    double efficiency = (double)N_detected / N_total;
    double sd = sqrt(efficiency * (1 - efficiency) / N_total);

    double fraction_scattered_same = (double)100*N_detected_scattered_same / N_detected;
    double fraction_scattered_other = (double)100*N_detected_scattered_other / N_detected;
    double fraction_undetected = (double)100*N_undetected / N_total;

    std::cout << "Efficiency: " << efficiency << " ± " << sd << std::endl;
    std::cout << "Fraction scattered in same detector: " << fraction_scattered_same << std::endl;
    std::cout << "Fraction scattered to other detector: " << fraction_scattered_other << std::endl;
    std::cout << "Fraction undetected: " << fraction_undetected << std::endl;

    return efficiency;
}

void plotThetaDistribution(double E_gamma=0.511, int N_samples=1000000) {
    TH1F* hist = new TH1F("Theta_dist", "Theta Distribution; #theta (rad);Counts", 100, 0, TMath::Pi());

    for (int i = 0; i < N_samples; ++i) {
        hist->Fill(simulateTheta(E_gamma));
    }

    hist->Draw();
}


void run_simulation() {
    double eff = efficiency(0.511, 1000000);
    
    plotThetaDistribution(0.511);
}