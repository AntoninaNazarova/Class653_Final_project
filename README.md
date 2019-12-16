# Class653_Final_project
 
Title: 
Computationally driven chemical kinetics for mechanistic modelling of complex catalytic reactions

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


Results and discussion:
Study the performance of the OpenMP-based grid search implementing 4th order classic RK solver for kinetic study of nonstiff 2 substrate 2 intermediate transitional metal-catalyzed reaction mechanism. The total number of threads will be equaled the number of implemented different values of rate constants ka (first i1 loop; i1 max = 12, 22).  The grid search will employ LSM minimization when compared computed results (concentration profile) - with the experimental data within one thread. Reliability of the corresponding coefficients will be verified via graphical superposition of the derived computed concentration profiles with the experimental ones. Initial conditions will be selected based on experimental data assuming 2% of the standard deviation error.

Description of the code. Fifth-order Runge-Kutta method.
The emerged system of ODEs was examined to preserve little to no stiffness, allowing solution in the form of the explicit integration of 5th order Runge-Kutta method. The method embades value y(n+1) from previous y(n) in addition to the averaged sum of four previous increments, chosed depending on the slope at the midpoint of the integrated interval:
y(n+1)=y(n)+h/6(k_1+2k_2+2k_3+k4);
k_1=f(x(n),y(n)),
k_2=f(x(n)+h/2,y(n)+h/2*k_1),
k_3=f(x(n)+h/2, y(n)+h/2*k_2),
k_4=f(x(n)+h, y(n)_h*k_3).
The step size was declared to be 0.01 or less to increase the resolution of derived integral.




