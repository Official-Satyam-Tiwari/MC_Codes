#include "TRandom3.h"
#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"
#include <iostream>

void basic1() {
    double M = 0.6;
    double m1 = 0.25, m2 = 0.25;

    TGenPhaseSpace event;
    TLorentzVector parent(0, 0, 0, M); 
    double masses[2] = {m1, m2}; 

    if (!event.SetDecay(parent, 2, masses)) {
        std::cout << "Phase space not valid!" << std::endl;
        return;
    }

    if (event.Generate()) {
        TLorentzVector *p1 = event.GetDecay(0);
        TLorentzVector *p2 = event.GetDecay(1);
        std::cout << "Decay generated successfully!" << std::endl;
        std::cout << "p1: "; p1->Print();
        std::cout << "p2: "; p2->Print();
    } else {
        std::cout << "Decay generation failed!" << std::endl;
    }
}