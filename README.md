# Class653_Final_project
 
Title: 
Computationally driven chemical kinetics for mechanistic modelling of complex catalytic reactions using OpenMPI 

Introduction:
Modeling description of an organometallic transformation involves an extensive framework of ordinary differential equasions (ODEs) of reactants ([A], [P], [Z]) and active catalytic species ([A·cat], [cat], [A·cat·Z]). For the copper(I)-catalysed azide-iodoalkyne cycloaddition reaction, a kinetic model can be descriped as following:

𝐝[𝐀]/𝐝𝐭=−𝒌_𝑨*[𝑨]*([𝑷]+[𝑨]+const1)+𝒌_(−𝑨)*(−[𝑨]+[𝒁]+const0);
𝒅[𝒁]/𝒅𝒕=−𝒌_𝒛*(−[𝑨]+[𝒁]+const0)*[𝒁]+𝒌_(−𝒛)*(−[𝑷]−[𝒁]+const2); 
𝒅[𝑷]/𝒅𝒕= 𝒌_𝟐*[𝑨∙𝒄𝒂𝒕∙𝒁]=𝒌_𝟐*(−[𝑷]−[𝒁]+const2), where [A],[Z] and [P]- monitoring substrate concentrations; 𝒌_𝑨,𝒌_(−𝑨),𝒌_𝒛,𝒌_(−𝒛),𝒌_𝟐 - unknown reaction kinetic parameters.

For the detailed study of emerged catalytic mechanism and for it's improvement in an industrial scale, non-equilibrium reaction rate constants and parameters are needed to be calculated – ka, k-a, kz, k-z, k2. A straighforward grid search employing a descreet step of 0.5(kx ≈ [0; 5]) in the frames of classic 4th order Runge-Kutta method has been probed for the data dense and normal volume experimental profiles. Determining of the reaction constants was gained via superimposing of the experimental profile  with the computed one (in the frames of LMS method). This approach for the inverse problem solution in chemical kinetics was directly proportional to the density of an experimental set and sometimes required more than 24 hours. Effective usage of different levels of heterogeneous parallelism on multiple core CPUs and GPU version implemented for rate law integration algorithms can tramendously improve mechanism modelling performance while redusing computational time.

The problem: 
High-fidelity computing of complex catalytic reaction kinetics without parallelizing chemistry integration on several processors or multiple cores (CPU) is time-consuming. In addition to computing approaches, explicit and emplicit integration methods are needed to be employed to solve a set of independent ODEs involving substrate-related finite rate equations. Computational challenges:
a) Chemical stiffness (rapidly changed reactivity profile—rapidly depleting moieties, fast-timing reversible reaction steps);
b) Large pool of catalytic cycle-involved species.
Nowadays, modern parallel computing technologies allow efficient and fast yet reliable analysis of the informativity of kinetic data in the mathematical interpretation of measurement results.

What has been done before:
HPC kinetic simulation were successfully implemented for combustion chemistry (heavy hydrocarbons, biodiesel—more than 2000 involved species) or hydrogen/carbon monoxide or methane reduction (~53 species; 634 irreversible steps) using 5th order RKCK or 2nd order RKC methods. Explicit integration algorithms were parallelized on multiple core CPU using MPI (or OpenMP). GPU acceleration units (CUDA) demonstrated generally several times higher performance than single or multiple-core CPU versions. However, reported understudied kinetic systems did not indicated equilibrium prosseses nor they described a cyclic processes.  


What we are trying to achieve:
Study the performance of the MPI-based 4th order classic RK solver for kinetic study of nonstiff 2 substrate 2 intermediate transitional metal-catalyzed reaction mechanism. The total number of cores will be equaled the number of implemented different values of rate constants k2 - 10. The rough estimation of 5 key reactivity parameters (ka, k-a, kz, k-z, k2 ) will be derived via grid search employing LSM minimization when compared computed results (concentration profile) - with the experimental data within one core. 5 results corresponding to the min function within the one core solutions pool will be send to the MPI communicators for evaluation of the global min. Corresponding coefficients will be the most reliable kinetic constants. Initial conditions will be selected based on experimental data assuming 2% of the standard deviation error.


