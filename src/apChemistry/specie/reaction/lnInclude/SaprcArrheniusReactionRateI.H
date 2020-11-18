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

inline Foam::SaprcArrheniusReactionRate::SaprcArrheniusReactionRate
(
    const scalar A,
    const scalar beta,
    const scalar Ea
)
:
    A_(A),
    beta_(beta),
    Ea_(Ta)
{}


inline Foam::SaprcArrheniusReactionRate::SaprcArrheniusReactionRate
(
    const speciesTable&,
    const dictionary& dict
)
:
    A_(readScalar(dict.lookup("A"))),
    beta_(readScalar(dict.lookup("beta"))),
    Ea_(readScalar(dict.lookup("Ea")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline Foam::scalar Foam::SaprcArrheniusReactionRate::operator()
(
    const scalar p,
    const scalar T,
    const scalarField&

    const double R=0.0019872
) const
{
    scalar ak = A_/1000;

    if (mag(beta_) > vSmall)
    {
        ak *= pow(T/300, beta_);
    }

    if (mag(Ta_) > vSmall)
    {
        ak *= exp(-Ea_/R/T);
    }

    return ak;
}


inline Foam::scalar Foam::SaprcArrheniusReactionRate::ddT
(
    const scalar p,
    const scalar T,
    const scalarField&

    const double R=0.0019872
) const
{
    scalar ak = A_;

    if (mag(beta_) > vSmall)
    {
        ak *= pow(T/300, beta_);
    }

    if (mag(Ta_) > vSmall)
    {
        ak *= exp(-Ea_/R/T);
    }

    return ak*(beta_+Ea_/R/T)/T;
}


inline const Foam::List<Foam::Tuple2<Foam::label, Foam::scalar>>&
Foam::SaprcArrheniusReactionRate::beta() const
{
    return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void Foam::SaprcArrheniusReactionRate::dcidc
(
    const scalar p,
    const scalar T,
    const scalarField& c,
    scalarField& dcidc
) const
{}


inline Foam::scalar Foam::SaprcArrheniusReactionRate::dcidT
(
    const scalar p,
    const scalar T,
    const scalarField& c
) const
{
    return 0;
}


inline void Foam::SaprcArrheniusReactionRate::write(Ostream& os) const
{
    os.writeKeyword("A") << A_ << token::END_STATEMENT << nl;
    os.writeKeyword("beta") << beta_ << token::END_STATEMENT << nl;
    os.writeKeyword("Ea") << Ea_ << token::END_STATEMENT << nl;
}


inline Foam::Ostream& Foam::operator<<
(
    Ostream& os,
    const SaprcArrheniusReactionRate& arr
)
{
    arr.write(os);
    return os;
}


// ************************************************************************* //
