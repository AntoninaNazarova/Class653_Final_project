# Class653_Final_project
 
Motivation: +++Computationally driven development of novel chemoselective methods

Organometallic transformation involves an extensive framework of ODEs of reactants ([A], [P], [Z]) and active catalytic species ([A·cat], [cat], [A·cat·Z]). For detailed study of catalytic mechanism, non-equilibrium reaction rate constants and parameters are needed to be calculated – ka, k-a, kz, k-z, k2. kx ≈ [0; 5] with a discreet step 0.5 will overall require comparison of 105 solutions

𝐝[𝐀]/𝐝𝐭=−𝒌_𝑨*[𝑨]*([𝑷]+[𝑨]+const1)+𝒌_(−𝑨)*(−[𝑨]+[𝒁]+const0)

𝒅[𝒁]/𝒅𝒕=−𝒌_𝒛*(−[𝑨]+[𝒁]+const0)*[𝒁]+𝒌_(−𝒛)*(−[𝑷]−[𝒁]+const2) 

𝒅[𝑷]/𝒅𝒕= 𝒌_𝟐*[𝑨∙𝒄𝒂𝒕∙𝒁]=𝒌_𝟐*(−[𝑷]−[𝒁]+const2)


The problem: +++High-fidelity computing of complex catalytic reaction kinetics is time-consuming

An explicit and explicit integration methods are employed to solve a set of independent ODEs involving substrate-related finite rate equations. Computational challenges:
a) Chemical stiffness (rapidly changed reactivity profile—rapidly depleting moieties, fast-timing reversible reaction steps);
b) Large pool of catalytic cycle-involved species.

Modern parallel computing technologies allow efficient and fast yet reliable analysis of the informativity of kinetic data in the mathematical interpretation of measurement results.

What has been done before:
Explicit integration algorithms were parallelized on multiple core CPU using MPI (or OpenMPI).
GPU acceleration units (CUDA) demonstrated generally several times higher performance than single or multiple-core CPU versions.
HPC kinetic simulation were successfully implemented for combustion chemistry (heavy hydrocarbons, biodiesel—more than 2000 involved species) or hydrogen/carbon monoxide or methane reduction (~53 species; 634 irreversible steps) using 5th order RKCK or 2nd order RKC methods.

What are we trying to achieve:

Study the performance of the MPI-based 4th order classic RK solver for kinetic study of nonstiff 2 substrate 2 intermediate transitional metal-catalyzed reaction mechanism.
The total number of cores will be equaled the number of implemented different values of rate constants k2 - 10.
The rough estimation of 5 key reactivity parameters (ka, k-a, kz, k-z, k2 ) will be derived via grid search employing LSM minimization when compared computed results (concentration profile) - with the experimental data within one core.
5 results corresponding to the min function within the one core solutions pool will be send to the MPI communicators for evaluation of the global min. Corresponding coefficients will be the most reliable kinetic constants. 
Initial conditions will be selected based on experimental data assuming 2% of the standard deviation error.


