<a href="https://doi.org/10.5281/zenodo.4279172"><img src="https://zenodo.org/badge/DOI/10.5281/zenodo.4279172.svg" alt="DOI"></a>
https://zenodo.org/badge/DOI/10.5281/zenodo.4279172.svg

There two ways to use APFoam:

One (recommended): 
1. Untar and compile the OpenFOAM-6-AP (similar with the original OPFoam)
2. Compile applications (compile the solver you want to use)
2.1 cd applications/APChemFoam
     wmake
2.2 cd applications/APReactingFoam
     wmake
2.3 cd applications/APOnlyChemReactingFoam
     wmake
2.4 cd applications/APSteadyReactingFoam
     wmake

Two:

0. Compile the original OPFoam 
1. Compile the SRC (libs would be in $FOAM_USER_LIBBIN)
1.1 cd src/apChemistry/specie/ 
   wmake libso
1.2 cd src/apChemistry/reactionThermo/
   wmake libso
1.3 cd src/apChemistry/chemistryModel/
   wmake libso


2. Compile applications (compile the solver you want to use, solver would be in $FOAM_USER_APPBIN)

2.1 cd applications/APChemFoam
     add -lsapfoamchemistryModel into Make/options, EXE_LIBS
     wmake
2.2 cd applications/APReactingFoam
     add -lsapfoamchemistryModel into Make/options, EXE_LIBS
     wmake
2.3 cd applications/APOnlyChemReactingFoam
     add -lsapfoamchemistryModel into Make/options, EXE_LIBS
     wmake
2.4 cd applications/APSteadyReactingFoam
     add -lsapfoamchemistryModel into Make/options, EXE_LIBS
     wmake
