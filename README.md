# Summary of Lectures on Monte Carlo Simulations, ROOT, and Detector Efficiency

## Lec-01 (02-12-2024): **Random Number Generation and Distributions**
- **Objective**: Learn how to generate random numbers from different distributions and visualize them using ROOT.
- **Tasks**:
  - Generated random numbers from a normal distribution.
  - Plotted histograms for visualizing the distribution of generated data.
  - Explored the Poisson and Exponential distributions and generated random numbers from these distributions.
  - Verified the Central Limit Theorem (CLT) by adding multiple random variables from a Poisson distribution and observing the convergence toward a normal distribution.
  - Implemented the Klein-Nishina formula for simulating and plotting the differential cross-section of Compton scattering.
  
- **Homework**:
  - Verifying the CLT using the Exponential distribution.
  - Plotting histograms and visualizing data behavior for different distributions.

---

## Lec-02 (05-12-2024): **Exponential Distribution and Mean Lifetime**
- **Objective**: Investigate exponential distributions and verify the mean lifetime of particles through Monte Carlo simulations.
- **Key Concepts**:
  - **Exponential Distribution**: Explained how the exponential distribution describes processes like radioactive decay with memoryless properties.
  - **Mean Lifetime (τ)**: Validated the concept of mean lifetime in simulations, showing its calculation and fitting from data.
  - **Monte Carlo Techniques**: Applied Monte Carlo simulations to verify the exponential distribution properties.
  
- **Exercises**:
  - Performed simulations to validate the exponential distribution and its memoryless property.
  - Fit exponential distributions to data and analyzed how variations in the start time affected results.

---

## Lec-03 (05-12-2024): **JPET Detector Efficiency**
- **Objective**: Simulate the efficiency and acceptance of the JPET (Jagiellonian PET) detector using Monte Carlo methods.
- **Tasks**:
  - Simulated a 2D isotropic detector and calculated the efficiency using photon interaction probabilities (based on attenuation laws) and energy thresholds.
  - Extended the simulation to 2-gamma interactions, considering energy thresholds and detector interactions.
  - Implemented detector systems with varying geometries and calculated efficiencies for different configurations.
  - **Advanced Exercises**: Explored how efficiency varies with energy thresholds and simulated photon interactions in complex detector setups.

- **Key Concepts**:
  - Gamma photon interactions: simulated using angular distributions and exponential decay laws.
  - Energy deposition: photon energy was calculated using the Klein-Nishina formula.
  - Detectors: Simulated 2D and 3D detector systems and analyzed efficiencies for multi-photon events.

---

## Lec-04 (16-12-2024): **Inverse Transform Sampling**
- **Objective**: Learn and apply the Inverse Transform Sampling (ITS) technique for generating random samples from arbitrary distributions.
- **Steps for ITS**:
  - **Generate a Uniform Random Sample**: Start by generating a random number from a uniform distribution U(0,1).
  - **Find the Inverse CDF**: Use the inverse of the cumulative distribution function (CDF) to convert the uniform sample to the desired distribution.
  - **Example**: Applied this method to generate random numbers from an exponential distribution.
  
- **Tasks**:
  - Implemented the correct method for generating random numbers in polar and spherical coordinates using ITS.
  - **Correct Method for Polar Coordinates**: Handled radial distributions and corrected bias towards the center of the circle using the inverse CDF.
  - **Spherical Coordinates**: Generated random points within a sphere using appropriate PDFs and CDFs.

- **Key Concepts**:
  - ITS allows the generation of samples from any distribution by transforming uniform random samples.
  - Correct methods for sampling in polar and spherical coordinates, with applications in simulations involving spatial distributions.

---

## Lec-05 (20-12-2024): **Simulation Exercises and Detector Efficiency (Tasks from Lec-03)**
- **Objective**: Solve exercises and explore further detector simulations from Lec-03.
- **Tasks Solved**:
  - Calculated efficiencies for various detector configurations (including isotropic and anisotropic modules).
  - Validated results and visualized detector performance under different conditions (e.g., energy thresholds, module size).
  - Extended the analysis to more complex detector geometries and simulated multi-photon interactions.

---

## Conclusion:
The lectures provided a comprehensive understanding of Monte Carlo simulations, random number generation techniques, detector efficiency, and the properties of key distributions (like exponential and Poisson distributions). The exercises included both basic and advanced tasks, helping to build a solid foundation for simulating complex physical systems and detectors used in medical imaging and particle physics.

---
