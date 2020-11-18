{
    volScalarField& he = thermo.he();

    forAll(he,celli)
	{
	 scalar T0=T[celli];
	 scalar p0 = p[celli];
	 scalar h0=0;
	 forAll(Y,specieI)
	  {
	    h0 += Y[specieI][celli]*specieData[specieI].Hs(p0, T0);
          }
	}
    he.correctBoundaryConditions();
    thermo.correct();
}
