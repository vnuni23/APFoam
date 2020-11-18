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

template<class ReactionRate>
inline Foam::FallOffTwoKReactionRate<ReactionRate>::
FallOffTwoKReactionRate
(
    const ReactionRate& k1,
    const ReactionRate& k2,
    const thirdBodyEfficiencies& tbes
)
:
    k1_(k1),
    k2_(k2),
    thirdBodyEfficiencies_(tbes)
{
    forAll(tbes, i)
    {
        beta_.append(Tuple2<label, scalar>(i, tbes[i]));
    }
}


template<class ReactionRate>
inline Foam::FallOffTwoKReactionRate<ReactionRate>::
FallOffTwoKReactionRate
(
    const speciesTable& species,
    const dictionary& dict
)
:
    k1_(species, dict.subDict("k1")),
    k2_(species, dict.subDict("k2")),
    thirdBodyEfficiencies_(species, dict.subDict("thirdBodyEfficiencies"))
{
    forAll(thirdBodyEfficiencies_, i)
    {
        beta_.append
        (
            Tuple2<label, scalar>
            (
                i,
                thirdBodyEfficiencies_[i]
            )
        );
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ReactionRate>
inline Foam::scalar
Foam::FallOffTwoKReactionRate<ReactionRate>::operator()
(
    const scalar p,
    const scalar T,
    const scalarField& c
) const
{
    scalar Na=6.02214e20;  // 6.02e23x1e-3;  k2 is the reaction coeffiecent for 3rd order reaction .   
			   // k1[A][B]  equal k2[M][A][B], [M], [A], [B] in dimensions of [kmole/m3]
    const scalar k1 = k1_(p, T, c);
    const scalar k2M = k2_(p, T, c)*thirdBodyEfficiencies_.M(c)*Na;

//    Info<<"k = "<<k1 + k2M <<endl;
//    Info<<"k1="<<k1<<nl<<"k2M="<<k2M<<endl;
    return k1 + k2M; //kInf*(Pr/(1 + Pr))*F_(T, Pr);
    
}


template<class ReactionRate>
inline Foam::scalar
Foam::FallOffTwoKReactionRate<ReactionRate>::ddT
(
    const scalar p,
    const scalar T,
    const scalarField& c
) const
{
    const scalar k1 = k1_(p, T, c);
    const scalar k2 = k2_(p, T, c);
//    const scalar Pr = k0*thirdBodyEfficiencies_.M(c)/kInf;

    return 0; //(Pr/(1 + Pr))*F_(T, Pr)*kInf_.ddT(p, T, c);
}


template<class ReactionRate>
inline void Foam::FallOffTwoKReactionRate<ReactionRate>::dcidc
(
    const scalar p,
    const scalar T,
    const scalarField& c,
    scalarField& dcidc
) const
{

        forAll(beta_, i)
        {
            dcidc[i] = 0;
        }
}


template<class ReactionRate>
inline Foam::scalar
Foam::FallOffTwoKReactionRate<ReactionRate>::dcidT
(
    const scalar p,
    const scalar T,
    const scalarField& c
) const
{
/*
    const scalar M = thirdBodyEfficiencies_.M(c);

    if (M > small)
    {
        const scalar k0 = k1_(p, T, c);
        const scalar kInf = kInf_(p, T, c);

        const scalar Pr = k0*thirdBodyEfficiencies_.M(c)/kInf;
        const scalar F = F_(T, Pr);
        const scalar dPrdT =
            Pr*(k0_.ddT(p, T, c)/k0 - kInf_.ddT(p, T, c)/kInf - 1/T);
        const scalar dFdT = F_.ddT(Pr, F, dPrdT, T);

        return (dPrdT/(Pr*(1 + Pr)) + dFdT/F);
    }
    else
*/
    {
        return 0;
    }
}


template<class ReactionRate>
inline void Foam::FallOffTwoKReactionRate<ReactionRate>::write
(
    Ostream& os
) const
{
    os  << indent << "k1" << nl;
    os  << indent << token::BEGIN_BLOCK << nl;
    os  << incrIndent;
    k1_.write(os);
    os  << decrIndent;
    os  << indent << token::END_BLOCK << nl;

    os  << indent << "k2" << nl;
    os  << indent << token::BEGIN_BLOCK << nl;
    os  << incrIndent;
    k2_.write(os);
    os  << decrIndent;
    os  << indent << token::END_BLOCK << nl;


    os  << indent << "thirdBodyEfficiencies" << nl;
    os  << indent << token::BEGIN_BLOCK << nl;
    os  << incrIndent;
    thirdBodyEfficiencies_.write(os);
    os  << decrIndent;
    os  << indent << token::END_BLOCK << nl;
}


template<class ReactionRate>
inline Foam::Ostream& Foam::operator<<
(
    Ostream& os,
    const FallOffTwoKReactionRate<ReactionRate>& forr
)
{
    forr.write(os);
    return os;
}


// ************************************************************************* //
