/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::photolysisReactionRate::photolysisReactionRate
(
            const scalarField lambda0,
            const scalarField abs0,
            const scalarField qy0,
	    const scalarField J0
)
:
    lambda_(lambda0),
    abs_(abs0),
    qy_(qy0),
    nPoints_(lambda_.size()),
    J_(J0),
    deltaLambda_(0.*J_)
{
   for(int ii=1; ii<nPoints_-1; ii++)
   {
        deltaLambda_[ii]=0.5*(lambda_[ii+1]-lambda_[ii-1]);
   }
   deltaLambda_[0]=0.5*(lambda_[1]-lambda_[0]);
   deltaLambda_[nPoints_-1] =0.5*(lambda_[nPoints_-1]-lambda_[nPoints_-2]);


}


inline Foam::photolysisReactionRate::photolysisReactionRate
(
    const speciesTable&,
    const dictionary& dict
)
:
    lambda_(dict.lookup("waveLength")),
    abs_(dict.lookup("abs")),
    qy_(dict.lookup("qy")),
    nPoints_(lambda_.size()),
    J_(dict.lookup("J")),
    deltaLambda_(0.*J_)
{
   for(int ii=1; ii<nPoints_-1; ii++)
   {
	deltaLambda_[ii]=0.5*(lambda_[ii+1]-lambda_[ii-1]);
   }
   deltaLambda_[0]=0.5*(lambda_[1]-lambda_[0]);
   deltaLambda_[nPoints_-1] =0.5*(lambda_[nPoints_-1]-lambda_[nPoints_-2]);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline Foam::scalar Foam::photolysisReactionRate::operator()
(
    const scalar p,
    const scalar T,
    const scalarField&

) const
{

scalar k_=0;

for(int ii=0; ii<nPoints_;ii++)
{

k_ += J_[ii]*abs_[ii]*qy_[ii]*deltaLambda_[ii];
}
   Info<<"k="<<k_;
    return k_;
}


inline Foam::scalar Foam::photolysisReactionRate::ddT
(
    const scalar p,
    const scalar T,
    const scalarField&

) const
{
 return 0;
}


inline const Foam::List<Foam::Tuple2<Foam::label, Foam::scalar>>&
Foam::photolysisReactionRate::beta() const
{
    return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void Foam::photolysisReactionRate::dcidc
(
    const scalar p,
    const scalar T,
    const scalarField& c,
    scalarField& dcidc
) const
{}


inline Foam::scalar Foam::photolysisReactionRate::dcidT
(
    const scalar p,
    const scalar T,
    const scalarField& c
) const
{
    return 0;
}


inline void Foam::photolysisReactionRate::write(Ostream& os) const
{
    os.writeKeyword("wavelLength") << lambda_ << token::END_STATEMENT << nl;
    os.writeKeyword("abs") << abs_ << token::END_STATEMENT << nl;
    os.writeKeyword("qy") << qy_ << token::END_STATEMENT << nl;
}


inline Foam::Ostream& Foam::operator<<
(
    Ostream& os,
    const photolysisReactionRate& arr
)
{
    arr.write(os);
    return os;
}


// ************************************************************************* //
