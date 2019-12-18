# Class653_Final_project
 
Computationally driven chemical kinetics for mechanistic modelling of complex catalytic reactions

•	Introduction. 
High-fidelity computing of complex catalytic reaction kinetics is time-consuming unless chemistry integration is paralyzed on several processors or multiple cores (CPU).1-3 In addition to computing approaches, explicit and implicit integration methods are needed to be employed to solve a set of independent ODEs involving substrate-related finite rate equations. Computational challenges:
a) Chemical stiffness (usually is a consequence of a rapidly changed reactivity profile. Swiftly descending profile is usually signalizing about the presence of speedy depleting moieties, fast-timing reversible reaction steps);
b) Large pool of catalytic inner-cycle species (the majority of the catalytic reactions are multistep and may involve off-cycle species formation).
Nowadays, modern parallel computing technologies allow fast, efficient yet reliable analysis of kinetic data of mathematical interpretation of measurement results.

•	What has been done before.
Previously, HPC kinetic simulations were successfully implemented for the investigation of the combustion chemistry processes (for example, biodiesel is consisted of more than 2000 involved heavy hydrocarbon species) or reactions of carbon monoxide or methane reduction (~53 species; 634 irreversible steps). For both cases, 5th order RKCK (Runge-Kutta—Cash-Karp) or 2nd order RKC(Runge-Kutta-Chebyshev) methods were applied for the development of the complete mathematical models of emerged processes.4-5 Explicit integration algorithms were parallelized on multiple core CPU using MPI (or OpenMP). GPU acceleration units (CUDA terminology) demonstrated generally several times higher performance than single or multiple-core CPU versions, particularly for cases with more than 103 independent ODEs. However, reported understudied kinetic systems did not indicated equilibrium processes nor operated with cyclic process. 

•	Problem description.
Modeling description of an organometallic transformation involves an extensive framework of ordinary differential equations (ODEs) of reactants ([A]-iodoalkyne, [P]-product, [Z]-azide) and active catalytic species ([A·cat], [cat], [A·cat·Z]). For the copper(I)-catalyzed azide-iodoalkyne cycloaddition reaction, a kinetic model can be described as following:
𝐝[𝐀]/𝐝𝐭 = −𝒌𝑨·[𝑨]·([𝑷]+[𝑨]+const1) + 𝒌−𝑨·(−[𝑨]+[𝒁]+const0);
𝒅[𝒁]/𝒅𝒕 = −𝒌Z·[Z]·(−[𝑨]+[𝒁]+const0) + 𝒌−Z·(−[𝑷]−[𝒁]+const2); 
𝒅[𝑷]/𝒅𝒕 = 𝒌𝟐·(−[𝑷]−[𝒁]+const2), 
where 𝐝[𝐀]/𝐝𝐭, 𝒅[𝒁]/𝒅𝒕 and 𝒅[𝑷]/𝒅𝒕- reaction rates; [A], [Z] and [P]- monitoring substrate concentrations; 𝒌𝑨, 𝒌−𝑨, 𝒌Z, 𝒌−Z, 𝒌𝟐 - unknown reaction kinetic parameters.
For the detailed study of emerged catalytic mechanism and for it's improvement in an industrial scale, non-equilibrium reaction rate constants and parameters are required to be calculated – kA, k-A, kZ, k-Z, k2. A straightforward grid search employing a discreet step of 0.5 (kx ≈ [0; 5]) in the frames of classic 4th order Runge-Kutta method has been implemented. A relatively dense experimental data set of concentration values was probed. Time efficiency was proportional to the density of an experimental set requiring more than 24 hours for some cases. Determination of the reaction constants was gained via superimposing of the experimental profiles with the analytically derived ones (in the frames of LMS metrics). Current approach for the inverse problem solution in chemical kinetics was operated via direct problem estimation. Effective usage of different levels of heterogeneous parallelism on multiple core CPUs and GPU version implemented for the rate law integration algorithms can tremendously improve mechanism modelling performance while reducing computational time.

•	Computational approach and strategy.
Reactivity rate parameters determination is referred to the class of reverse problems in chemical kinetics, which has been solved in our approach by the grid search method.6 However, this tactic gives rough estimation of reaction rate parameters, when implemented large discreet value, which is usually the case when using one-core computing. Further refinement of the rate parameters was accomplished with a gradient descent method, which often resulted in biased solution (dependent on the initial conditions). Disadvantage of implementing small discreet values can be considered an exponential increase of calculation time required for the grid search.
The goal of current research project was to study the performance of the OpenMP-based grid search implementing 4th order classic RK solver for kinetic study of nonstiff two substrate two intermediate transitional metal-catalyzed reaction mechanism. The total number of threads was equaled to the number of implemented different values of rate constants ka (first i1 loop; i1 max = 12 (discretization step h=0.5) or 22 (discretization step h=0.25)). The grid search employed LSM minimization when compared computed results (concentration profile) - with the experimental data within one thread. Reliability of the corresponding coefficients was verified via graphical superposition of the derived computed concentration profiles with the experimental ones. Initial conditions will be selected based on experimental data assuming 2% of the standard deviation error.

•	Description of the code. Results and Discussion.
The emerged system of ODEs was examined to preserve little to no stiffness, allowing solution in the form of the explicit integration with 5th order Runge-Kutta method. The method embeds value y(n+1) from previous y(n) in addition to the averaged sum of four previous increments, chose depending on the slope at the midpoint of the integrated interval:
y(n+1) = y(n)+h/6(k1+2k2+2k3+k4);
k1=f(x(n), y(n)),
k2=f(x(n)+h/2, y(n)+h/2·k1),
k3=f(x(n)+h/2, y(n)+h/2·k2),
k4=f(x(n)+h, y(n)_h·k3).
The step size was declared to be 0.01 to increase the resolution of derived integral. 
The input files (.dat) contained spectroscopically derived concentration values of both substrates and a product in the time-fashioned domain. OpenMP parallelization (#pragma statements places in C code) with 12 threads required 4m15.774s of global time for the minimization computing, whereas 1 thread (regular grid search) needed 44m 1.761s for execution of the same instructions. LMS corresponded min sums were slightly different for 12 and 1 thread executions, however the values of the rate constants were identical. Implementation of the 22 threads with 0.25 discretization step required 67m 51.703s of computing time. Obviously, derived kA, k-A, kZ, k-Z, k2 rate parameters values were different compared to those derived with 0.5 discreet (Table 1). The correct values of rate parameters were taken those correspondent to the lower minimum LMS sum parameter. 
An interesting fact was that 0.01% difference in min values of corresponding LMS sums were referred to completely different rate constants sets. As such, for entries 3 and 4 two groups of reaction rate parameters kA=2.75, k-A=0.25, kZ=5.00, k-Z=2.00, k2=0.25 and kA=2.00, k-A=0.25, kZ=5.00, k-Z=1.50, k2=0.25 were regarded to almost identical sums of square differences -- 0.004103 and 0.004104 correspondingly. Graphical representations of derived concentration values for both sets were identical, however the numerical difference between kA and k-Z  parameters was critical for determination of the intermediates evolution profiles. The further refinement of the current ODEs system reaction parameters as well as the reaction model is a subject of follow-up studies.
Table 1. OpenMP computational speedup of explicit method for nonstiff chemical kinetics of complex catalytic reaction.

No entry	n of threads	descr. step h	computing time	LMS sum min	   rate parameters values
1           	1	           0.5	        44m 14.761s	 0.004455	      kA=5.0, k-A=0.5, kZ=5.5, k-Z=4.5, k2=0.5
2	           12	          0.5	         4m 15.774s	 0.005072	      kA=5.0, k-A=0.5, kZ=5.5, k-Z=4.5, k2=0.5
3           	22	          0.25	       70m.14.420s	 0.004104	      kA=2.0, k-A=0.25, kZ=5.0, k-Z=1.5, k2=0.25
4	           22	          0.25	       70m.14.420s	 0.004103	      kA=2.75, k-A=0.25, kZ=5.0, k-Z=2.0, k2=0.25






A							B 
 
C							D








Figure 1. Comparison of experimental and predicted concentration-time profiles using the proposed dynamic model. Experimental values of reactant concentrations vs time were superimposed with the computed ones employing the numerical Runge-Kutta method. A) Substrate concentration profile. Table 1, entry 3; B) Cubstrate concentration profile. Table 1, entry 4; C) Intermediate concentration profile. Table 1, entry 3; D) Intermediate concentration profile. Table 1, entry 4.

•	Conclusion
High-fidelity OpenMP grid search method was developed, optimized and probed for the mechanism elucidation of copper-catalyzed azide-iodoalkyne cycloaddition reaction. Computational data was found to be finely superimposed with the experimental data. The further investigation of the other types of ODEs systems for complex catalytic transformation studies and model developments is required. Development of novel methods for solving more complex non stiff chemical kinetics employing CUDA graphical processing units (GPUs) for total run-time minimization is under consideration.

Literature:
1.	Curtis, N. J.; Niemeyer, K. E.; Sung, C.-J., An investigation of GPU-based stiff chemical kinetics integration methods. Combustion and Flame 2017, 179, 312-324.
2.	Niemeyer, K. E.; Sung, C.-J., Accelerating moderately stiff chemical kinetics in reactive-flow simulations using GPUs. Journal of Computational Physics 2014, 256, 854-871.
3.	Stone, C. P.; Davis, R. L., Techniques for Solving Stiff Chemical Kinetics on Graphical Processing Units. Journal of Propulsion and Power 2013, 29 (4), 764-773.
4.	Byrne, G. D.; Hindmarsh, A. C., Stiff ODE solvers: A review of current and coming attractions. Journal of Computational Physics 1987, 70 (1), 1-62.
5.	E. Hairer, G. W., Solving Ordinary Differential Equasions II, 2nd ed. Springer Ser. Comput. Math. 2010, Springer-Verlag, Berlin, Heidelberg.
6.	Santosa, F.; Weitz, B., An inverse problem in reaction kinetics. Journal of Mathematical Chemistry 2011, 49 (8), 1507-1520.





