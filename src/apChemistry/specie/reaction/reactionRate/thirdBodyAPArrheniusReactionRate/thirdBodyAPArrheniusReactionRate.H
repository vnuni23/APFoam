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
    Foam::thirdBodyArrheniusReactionRate

Description
    Arrhenius reaction rate enhanced by third-body interaction.
    
    AP foam Arrhenius reaction rate  //add 19/03/21

SourceFiles
    thirdBodyAPArrheniusReactionRateI.H

\*---------------------------------------------------------------------------*/

#ifndef thirdBodyAPArrheniusReactionRate_H
#define thirdBodyAPArrheniusReactionRate_H

#include "APArrheniusReactionRate.H"
#include "thirdBodyEfficiencies.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

class thirdBodyAPArrheniusReactionRate;

Ostream& operator<<(Ostream&, const thirdBodyAPArrheniusReactionRate&);


/*---------------------------------------------------------------------------*\
              Class thirdBodyAPArrheniusReactionRate Declaration
\*---------------------------------------------------------------------------*/

class thirdBodyAPArrheniusReactionRate
:
    APArrheniusReactionRate
{
    // Private data

        thirdBodyEfficiencies thirdBodyEfficiencies_;
        List<Tuple2<label, scalar>> beta_;


public:

    // Constructors

        //- Construct from components
        inline thirdBodyAPArrheniusReactionRate
        (
            const scalar A,
            const scalar beta,
            const scalar Ea,
            const thirdBodyEfficiencies& tbes
        );

        //- Construct from dictionary
        inline thirdBodyAPArrheniusReactionRate
        (
            const speciesTable& species,
            const dictionary& dict
        );


    // Member Functions

        //- Return the type name
        static word type()
        {
            return "thirdBodyAPArrhenius";
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

        inline friend Ostream& operator<<
        (
            Ostream&,
            const thirdBodyAPArrheniusReactionRate&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "thirdBodyAPArrheniusReactionRateI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
