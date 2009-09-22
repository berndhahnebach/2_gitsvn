/***************************************************************************
 *   Copyright (c) J�rgen Riegel          (juergen.riegel@web.de) 2002     *
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


#include "PreCompiled.h"

#ifndef _PreComp_
#endif

#include <Base/Writer.h>

#include "kdl/chain.hpp"
#include "kdl/chainfksolver.hpp"
#include "kdl/chainfksolverpos_recursive.hpp"
#include "kdl/frames_io.hpp"
#include "kdl/chainiksolver.hpp"
#include "kdl/chainiksolvervel_pinv.hpp"
#include "kdl/chainjnttojacsolver.hpp"
#include "kdl/ChainIkSolverPos_NR.hpp"

#include "Robot6Axis.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
    #define M_PI    3.14159265358979323846 /* pi */
#endif

#ifndef M_PI_2
    #define M_PI_2  1.57079632679489661923 /* pi/2 */
#endif

using namespace Robot;
using namespace Base;
using namespace KDL;


TYPESYSTEM_SOURCE(Robot::Robot6Axis , Base::Persistence);

Robot6Axis::Robot6Axis()
{
	Chain KukaIR16;

	// Puma 560
#if 0
    KukaIR16.addSegment(Segment());
    KukaIR16.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,M_PI_2,0.0,0.0),
                               RigidBodyInertia(0,Vector::Zero(),RotationalInertia(0,350,0,0,0,0))));
    KukaIR16.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(431.8,0.0,0.0,0.0),
                               RigidBodyInertia(17.4,Vector(-.3638,.006,.2275),RotationalInertia(0.13,0.524,0.539,0,0,0))));
    KukaIR16.addSegment(Segment());
    KukaIR16.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(20.3,-M_PI_2,150,0.0),
                               RigidBodyInertia(4.8,Vector(-.0203,-.0141,.070),RotationalInertia(0.066,0.086,0.0125,0,0,0))));
    KukaIR16.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,M_PI_2,431.8,0.0),
                               RigidBodyInertia(0.82,Vector(0,.019,0),RotationalInertia(1.8e-3,1.3e-3,1.8e-3,0,0,0))));
    KukaIR16.addSegment(Segment());
    KukaIR16.addSegment(Segment());
    KukaIR16.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,-M_PI_2,0.0,0.0),
                               RigidBodyInertia(0.34,Vector::Zero(),RotationalInertia(.3e-3,.4e-3,.3e-3,0,0,0))));
    KukaIR16.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,0.0,0.0,0.0),
                               RigidBodyInertia(0.09,Vector(0,0,.032),RotationalInertia(.15e-3,0.15e-3,.04e-3,0,0,0))));
    KukaIR16.addSegment(Segment());
#endif
#if 0
	// Kuka IR16
    //KukaIR16.addSegment(Segment());
 	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(260  ,-M_PI_2  ,576  ,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(680  ,0        ,0    ,0       )));
    //KukaIR16.addSegment(Segment());
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI_2   ,0    ,/*-M_PI_2*/0 )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,-M_PI_2  ,-670 ,0       )));
    //KukaIR16.addSegment(Segment());
    //KukaIR16.addSegment(Segment());
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI_2   ,0    ,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI     ,-158 ,0       )));
    //KukaIR16.addSegment(Segment());
#endif
	// Kuka IR210
#if 0
    KukaIR16.addSegment(Segment());
 	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(350  ,-M_PI_2  ,750  ,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(1250 ,0        ,0    ,0       )));
    KukaIR16.addSegment(Segment());
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI_2   ,0    ,-M_PI_2 )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,-M_PI_2  ,-1025,0       )));
    KukaIR16.addSegment(Segment());
    KukaIR16.addSegment(Segment());
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI_2   ,0    ,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI     ,-250 ,0       )));
    KukaIR16.addSegment(Segment());
#endif

	// Kuka IR500
#if 1
 	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(500  ,-M_PI_2  ,1045 ,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(1300 ,0        ,0    ,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(55   ,M_PI_2   ,0    ,-M_PI_2 )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,-M_PI_2  ,-1025,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI_2   ,0    ,0       )));
	KukaIR16.addSegment(Segment(Joint(Joint::RotZ),Frame::DH(0    ,M_PI     ,-300 ,0       )));
#endif

	// for now and testing
    Kinematic = KukaIR16;

	// Create joint array
    unsigned int nj = KukaIR16.getNrOfJoints();
    Actuall = JntArray(nj);

	// get the actuall TCP out of tha axis
	calcTcp();
}

Robot6Axis::~Robot6Axis()
{
}

unsigned int Robot6Axis::getMemSize (void) const
{
	return 0;
}

void Robot6Axis::Save (Writer &/*writer*/) const
{
}

void Robot6Axis::Restore(XMLReader &/*reader*/)
{
}



bool Robot6Axis::setTo(const Placement &To)
{
	//Creation of the solvers:
	ChainFkSolverPos_recursive fksolver1(Kinematic);//Forward position solver
	ChainIkSolverVel_pinv iksolver1v(Kinematic);//Inverse velocity solver
	ChainIkSolverPos_NR iksolver1(Kinematic,fksolver1,iksolver1v,100,1e-6);//Maximum 100 iterations, stop at accuracy 1e-6
	 
	//Creation of jntarrays:
	JntArray result(Kinematic.getNrOfJoints());
	 
	//Set destination frame
	Frame F_dest = Frame(KDL::Rotation::Quaternion(To.getRotation()[0],To.getRotation()[1],To.getRotation()[2],To.getRotation()[3]),KDL::Vector(To.getPosition()[0],To.getPosition()[1],To.getPosition()[2]));
	 
	// solve
	if(iksolver1.CartToJnt(Actuall,F_dest,result) < 0)
		return false;
	else{
		Actuall = result;
		Tcp = F_dest;
		return true;
	}
}

Base::Placement Robot6Axis::getTcp(void)
{
	double x,y,z,w;
	Tcp.M.GetQuaternion(x,y,z,w);
	return Base::Placement(Base::Vector3d(Tcp.p[0],Tcp.p[1],Tcp.p[2]),Base::Rotation(x,y,z,w));
}

bool Robot6Axis::calcTcp(void)
{
    // Create solver based on kinematic chain
    ChainFkSolverPos_recursive fksolver = ChainFkSolverPos_recursive(Kinematic);
 
     // Create the frame that will contain the results
    KDL::Frame cartpos;    
 
    // Calculate forward position kinematics
    int kinematics_status;
    kinematics_status = fksolver.JntToCart(Actuall,cartpos);
    if(kinematics_status>=0){
        Tcp = cartpos;
		return true;
    }else{
        return false;
    }
}

bool Robot6Axis::setAxis(int Axis,float Value)
{
	Actuall(Axis) = Value*(M_PI/180); // degree to radiants

	return calcTcp();
}

float Robot6Axis::getAxis(int Axis)
{
	return (float) (Actuall(Axis)/(M_PI/180)); // radian to degree
}

void Robot6Axis::exportChain(const char* FileName)
{

}

void Robot6Axis::importChain(const char* FileName)
{

}
 