
/*
 * Copyright (C) 2000-2001 QuantLib Group
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.org/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, please email quantlib-users@lists.sourceforge.net
 * The license is also available at http://quantlib.org/LICENSE.TXT
 *
 * The members of the QuantLib Group are listed in the Authors.txt file, also
 * available at http://quantlib.org/group.html
*/

/*! \file bisection.cpp
    \brief bisection 1-D solver

    \fullpath
    ql/Solvers1D/%bisection.cpp
*/

// $Id$

/* The implementation of the algorithm was inspired by
 * "Numerical Recipes in C", 2nd edition, Press, Teukolsky, Vetterling, Flannery
 * Chapter 9
 */


#include <ql/Solvers1D/bisection.hpp>

namespace QuantLib {

    namespace Solvers1D {

        double Bisection::solve_(const ObjectiveFunction& f,
                                 double xAccuracy) const {

            double dx, xMid, fMid;

            // Orient the search so that f>0 lies at root_+dx
            if (fxMin_ < 0.0) {
                dx = xMax_-xMin_;
                root_ = xMin_;
            } else {
                dx = xMin_-xMax_;
                root_ = xMax_;
            }

            while (evaluationNumber_<=maxEvaluations_) {
                dx /= 2.0;
                xMid=root_+dx;
                fMid=f(xMid);
                evaluationNumber_++;
                    if (fMid <= 0.0)
                        root_=xMid;
                    if (QL_FABS(dx) < xAccuracy || fMid == 0.0) {
                        return root_;
                    }
            }
            throw Error("Bisection: maximum number of function evaluations (" +
                            IntegerFormatter::toString(maxEvaluations_) +
                            ") exceeded");

            QL_DUMMY_RETURN(0.0);
        }

    }

}
