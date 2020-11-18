// readin the dictionary

IOdictionary pollutionSourceDict
(
   IOobject
    (
        "pollutionSourceProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);
label nRegions=readLabel(pollutionSourceDict.lookup("nPollutionRegions") );

volScalarField Srho_pollution
(
    IOobject
    (
        "Srho_pollution",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("a",rho.dimensions()/dimTime, 0.)
);
PtrList<volScalarField> SYi_pollution(Y.size());

for(int kk=0; kk<Y.size(); kk++)
{
 SYi_pollution.set
  (
   kk,
   new volScalarField
   (
    IOobject
    (
        "Srho_pollution",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("a",rho.dimensions()/dimTime, 0.)
   )
  );

}

for(int regionI=0; regionI<nRegions; regionI++)
{

    dictionary dictRegionI = pollutionSourceDict.subDict("pollutionSourceRegion"+name(regionI));
    scalar massRate_pollution = 0; // readScalar(dictRegionI.lookup("pollutionMassRate") );
    dictionary pollutionComposition(dictRegionI.subDict("pollutionComposition"));
    scalarField Ypollution(Y.size(),0);
    forAll(Y,kk)
     {

	Ypollution[kk]=pollutionComposition.lookupOrDefault<scalar>(Y[kk].name(), 0.);
	massRate_pollution += Ypollution[kk];
     }
    scalar Ytot=sum(Ypollution);
    forAll(Y,kk)
     {

       Ypollution[kk] /= Ytot;
     }

    dictionary box(dictRegionI.subDict("box"));
    vector boxP1(box.lookup("p1"));
    vector boxP2(box.lookup("p2"));

    scalar Xmin=min(boxP1[0],boxP2[0]);
    scalar Ymin=min(boxP1[1],boxP2[1]);
    scalar Zmin=min(boxP1[2],boxP2[2]);

    scalar Xmax=max(boxP1[0],boxP2[0]);
    scalar Ymax=max(boxP1[1],boxP2[1]);
    scalar Zmax=max(boxP1[2],boxP2[2]);

    scalarField regionIndex(mesh.V().size(),0);

    forAll(regionIndex,celli)
     {
       vector p0=mesh.C()[celli];
       if(p0[0]>=Xmin&&p0[0]<=Xmax)
       {
   	if(p0[1]>=Ymin&&p0[1]<=Ymax)
         {
           if(p0[2]>=Zmin&&p0[2]<=Zmax) regionIndex[celli]=1.0;
         }
       }

     }

   scalar VolumeSource=gSum(mesh.V()*regionIndex);
   scalar Srho_0 = massRate_pollution / VolumeSource;
   forAll(Srho_pollution,celli)
    {
       Srho_pollution[celli] +=Srho_0*regionIndex[celli];
       forAll(Y,kk)  SYi_pollution[kk][celli] += Srho_0*regionIndex[celli]*Ypollution[kk];
    }
    Info<< "set the "<<regionI<<"th source region bounding box "<<vector(Xmin,Ymin,Zmin)<<" "<<vector(Xmax, Ymax, Zmax)<<nl<<"effecient volume  "<<VolumeSource<<" m^3, with source rate: "<<Srho_0<<endl;

}



