/***************************************************************************
 *   Copyright (c) Konstantinos Poulios      (logari81@gmail.com) 2011     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef FREEGCS_GCS_H
#define FREEGCS_GCS_H

#include "SubSystem.h"

namespace GCS
{

    ///////////////////////////////////////
    // Solver
    ///////////////////////////////////////

    enum SolveStatus {
        Success = 0,   // Found a solution zeroing the error function
        Converged = 1, // Found a solution minimizing the error function
        Failed = 2     // Failed to find any solution
    };

//    enum ConstrainStatus {
//        Well = 0,  // Well-constrained system
//        Under = 1, // Under-constrained system
//        Over = 2   // Over-constrained system
//    };

/*
    class JacobianMatrix
    {
    private:
        std::map<Constraint *,MAP_pD_D > matrix;
    public:
        JacobianMatrix();
        double operator() (Constraint *constr, double *param);
        void set(Constraint *constr, double *param, double value);
        void remove(Constraint *constr);
    };
*/

    class System
    {
    // This is the main class. It holds all constraints and information
    // about partitioning into subsystems and solution strategies
    private:
        std::vector<Constraint *> clist;

//        JacobianMatrix jacobi; // jacobi matrix of the residuals

        std::map<Constraint *,VEC_pD > c2p; // constraint to parameter adjacency list
        std::map<double *,std::vector<Constraint *> > p2c; // parameter to constraint adjacency list

        std::vector<SubSystem *> subsystems;
        void clearSubSystems();

        MAP_pD_D reference;
        void clearReference();
        void resetToReference();

        MAP_pD_pD reductionmap; // for simplification of equality constraints

        bool init;
    public:
        System();
        System(std::vector<Constraint *> clist_);
        ~System();
        
        void clear();
        void clearLevel(int level);

        int addConstraint(Constraint *constr);
        void removeConstraint(Constraint *constr);

        int addConstraintEqual(double *param1, double *param2, int level=0);
        int addConstraintP2PDistance(Point &p1, Point &p2, double *distance, int level=0);
        int addConstraintP2PAngle(Point &p1, Point &p2, double *angle,
                                  double incr_angle, int level=0);
        int addConstraintP2PAngle(Point &p1, Point &p2, double *angle, int level=0);
        int addConstraintP2LDistance(Point &p, Line &l, double *distance, int level=0);
        int addConstraintPointOnLine(Point &p, Line &l, int level=0);
        int addConstraintParallel(Line &l1, Line &l2, int level=0);
        int addConstraintPerpendicular(Line &l1, Line &l2, int level=0);

        int addConstraintP2PCoincident(Point &p1, Point &p2, int level=0);
        int addConstraintHorizontal(Line &l, int level=0);
        int addConstraintHorizontal(Point &p1, Point &p2, int level=0);
        int addConstraintVertical(Line &l, int level=0);
        int addConstraintVertical(Point &p1, Point &p2, int level=0);
        int addConstraintCoordinateX(Point &p, double *x, int level=0);
        int addConstraintCoordinateY(Point &p, double *y, int level=0);
        int addConstraintArcRules(Arc &a, int level=0);
        int addConstraintPointOnCircle(Point &p, Circle &c, int level=0);
        int addConstraintPointOnArc(Point &p, Arc &a, int level=0);
        int addConstraintTangent(Line &l, Circle &c, int level=0);
        int addConstraintTangent(Line &l, Arc &a, int level=0);
        int addConstraintLine2Arc(Point &p1, Point &p2, Arc &a, int level=0);
        int addConstraintArc2Line(Arc &a, Point &p1, Point &p2, int level=0);

        void initSolution(VEC_pD &params);

        int solve(int isFine=1);
        int solve(VEC_pD &params, int isFine=1);
        int solve(SubSystem *subsys, int isFine=1);
        int solve(SubSystem *subsysA, SubSystem *subsysB, int isFine=1);

        void getSubSystems(std::vector<SubSystem *> &subsysvec);
        void applySolution();

        bool isInit() { return init; }

        void calcJacobi();
//        int analyse();
    };

    ///////////////////////////////////////
    // BFGS Solver parameters
    ///////////////////////////////////////
    #define XconvergenceRough 1e-8
    #define XconvergenceFine  1e-10
    #define smallF            1e-20
    #define MaxIterations     500 //Note that the total number of iterations allowed is MaxIterations *xLength

    ///////////////////////////////////////
    // Helper elements
    ///////////////////////////////////////

    void free(VEC_pD &doublevec);
    void free(std::vector<Constraint *> &constrvec);
    void free(std::vector<SubSystem *> &subsysvec);


} //namespace GCS

#endif // FREEGCS_GCS_H