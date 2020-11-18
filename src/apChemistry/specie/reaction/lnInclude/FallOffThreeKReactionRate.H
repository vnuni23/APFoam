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

Class
    Foam::FallOffThreeKReactionRate

Description
    General class for handling unimolecular/recombination fall-off reactions.

SourceFiles
    FallOffThreeKReactionRateI.H

\*---------------------------------------------------------------------------*/

#ifndef FallOffThreeKReactionRate_H
#define FallOffThreeKReactionRate_H

#include "thirdBodyEfficiencies.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

template<class ReactionRate>
class FallOffThreeKReactionRate;

template<class ReactionRate>
inline Ostream& operator<<
(
    Ostream&,
    const FallOffThreeKReactionRate<ReactionRate>&
);


/*---------------------------------------------------------------------------*\
                    Class FallOffThreeKReactionRate Declaration
\*---------------------------------------------------------------------------*/

template<class ReactionRate>
class FallOffThreeKReactionRate
{
    // Private data

        ReactionRate k1_;
        ReactionRate k2_;
	ReactionRate k3_;
        thirdBodyEfficiencies thirdBodyEfficiencies_;
        List<Tuple2<label, scalar>> beta_;


public:

    // Constructors

        //- Construct from components
        inline FallOffThreeKReactionRate
        (
            const ReactionRate& k1,
            const ReactionRate& k2,
            const ReactionRate& k3,
            const thirdBodyEfficiencies& tbes
        );

        //- Construct from dictionary
        inline FallOffThreeKReactionRate
        (
            const speciesTable& species,
            const dictionary& dict
        );


    // Member Functions

        //- Return the type name
        static word type()
        {
            return ReactionRate::type()  + "FallOffThreeK";
        }

        inline scalar operator()
        (
            const scalar p,
            const scalar T,
            const scalarField& c
        ) const;

        inline scalar ddT
        (
            const scalar p,
            const scalar T,
            const scalarField& c
        ) const;

        //- Third-body efficiencies (beta = 1-alpha)
        //  non-empty only for third-body reactions
        //  with enhanced molecularity (alpha != 1)
        inline const List<Tuple2<label, scalar>>& beta() const
        {
            return beta_;
        }

        //- Species concentration derivative of the pressure dependent term
        inline void dcidc
        (
            const scalar p,
            const scalar T,
            const scalarField& c,
            scalarField& dcidc
        ) const;

        //- Temperature derivative of the pressure dependent term
        inline scalar dcidT
        (
            const scalar p,
            const scalar T,
            const scalarField& c
        ) const;

        //- Write to stream
        inline void write(Ostream& os) const;


    // Ostream Operator

        friend Ostream& operator<< <ReactionRate>
        (
            Ostream&,
            const FallOffThreeKReactionRate<ReactionRate>&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "FallOffThreeKReactionRateI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
