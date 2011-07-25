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
#include <iostream>
#include <Eigen/QR>

using namespace Eigen;

// minimizes ( 0.5 * x^T * H * x + g^T * x ) under the condition ( A*x + c = 0 )
// it returns the solution in x, the row-space of A in Y, and the null space of A in Z
int qp_eq(MatrixXd &H, VectorXd &g, MatrixXd &A, VectorXd &c,
           VectorXd &x, MatrixXd &Y, MatrixXd &Z)
{
    FullPivHouseholderQR<MatrixXd> qrAT(A.transpose());
    MatrixXd Q = qrAT.matrixQ ();

    size_t rows = qrAT.rows();
    size_t cols = qrAT.cols();
    size_t r = qrAT.rank();

    assert(rows >= cols);
    if (r != cols)
        return -1;

    // A^T = Q*R*P^T = Q1*R1*P^T
    // Q = [Q1,Q2], R=[R1;0]
    // Y = Q1 * inv(R^T) * P^T
    // Z = Q2
    Y = qrAT.matrixQR().topRows(cols)
                       .triangularView<Upper>()
                       .transpose()
                       .solve<OnTheRight>(Q.leftCols(r))
        * qrAT.colsPermutation().transpose();
    Z = Q.rightCols(rows-r);

    MatrixXd ZTHZ = Z.transpose() * H * Z;
    VectorXd rhs = Z.transpose() * (H * Y * c - g);

    VectorXd y = ZTHZ.colPivHouseholderQr().solve(rhs);

    x = - Y * c + Z * y;

    return 0;
}