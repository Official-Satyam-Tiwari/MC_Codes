# Monte Carlo Simulations for J-PET Detectors

## Overview

This repository contains C++ code implementations for Monte Carlo simulations, developed as part of the "Lectures on Monte Carlo Simulations" by Prof. Pawel Moskal at the Jagiellonian University, Poland. The codes focus on simulations relevant to J-PET detectors, covering probability distribution sampling, Compton scattering, detector efficiency, and more. The simulations utilize the ROOT framework for random number generation, histogramming, and visualization.

The accompanying manual, *PET UJ Raport nr 04/2025*, provides detailed explanations of the theoretical background, algorithms, and code snippets. This repository hosts the complete, executable code for the simulations described in the manual.

## Prerequisites

To run the codes, you need the following:

- **C++ Compiler**: A C++11 compatible compiler (e.g., g++).
- **ROOT Framework**: Install ROOT (version 6 or later) from https://root.cern.
- **Dependencies**: Ensure ROOT libraries (e.g., `TRandom3`, `TH1D`, `TCanvas`) are accessible.
- **Optional Tools**: For advanced simulations (e.g., 3D geometry, Ps decay), install GATE and Geant4 as described in the manual.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Official-Satyam-Tiwari/MC-Codes.git
   cd MC-Codes
   ```

2. Set up ROOT:

   - Follow instructions at https://root.cern/install.
   - Ensure ROOT is in your `PATH` and libraries are linked (e.g., `root-config --cflags --libs`).

3. Compile and run a program:

   ```bash
   g++ -o program_name source_file.cpp `root-config --cflags --libs`
   ./program_name
   ```

4. For advanced simulations, install GATE and Geant4 as per the manual's preparation section.

## Usage

Each program is standalone and can be compiled and executed independently. Example command:

```bash
root -l program.cpp
[1]: function()
```

Output files (e.g., histograms, plots) are generated as ROOT canvases or saved as PNG images (e.g., `efficiency_vs_ethresh_2gamma.png`). Refer to the manual for expected outputs and figure descriptions.

## Key Features

- **Probability Distributions**: Sample from Normal, Custom, Poisson, and Exponential distributions using ROOT's `TRandom3`.
- **Compton Scattering**: Implement Klein-Nishina formula for realistic scattering angle and energy distributions.
- **Detector Efficiency**: Simulate gamma-ray detection in various geometries, from single detectors to circular and square arrays.
- **Central Limit Theorem**: Verify CLT using Poisson and Exponential distributions.
- **Fun Simulations**: Explore classic Monte Carlo problems like the Birthday Paradox and Monte Hall Problem.
- **Modularity**: Common functions (e.g., `SimulateDistance`, `SimulateElectronEnergy`) are reusable across programs.

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Add or modify code, ensuring consistency with the manual's structure.
4. Test your changes with ROOT.
5. Submit a pull request with a clear description of changes.

Please adhere to the coding style used in the manual (e.g., consistent naming, comments for key steps).

## References

- *PET UJ Raport nr 04/2025*: "Lectures on Monte Carlo Simulations" by Prof. Pawel Moskal.
- ROOT Framework: https://root.cern.
- GitHub Repository: https://github.com/Official-Satyam-Tiwari/MC-Codes.
- J-PET Project: http://koza.if.uj.edu.pl.

## Contact

For questions or support, contact:

- Satyam Tiwari: satyam.tiwari@doctoral.uj.edu.pl
