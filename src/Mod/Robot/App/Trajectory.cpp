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
#include "kdl/path_line.hpp"
#include "kdl/path_roundedcomposite.hpp"
#include "kdl/trajectory_composite.hpp"

#include "Trajectory.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
    #define M_PI    3.14159265358979323846 /* pi */
#endif

#ifndef M_PI_2
    #define M_PI_2  1.57079632679489661923 /* pi/2 */
#endif

using namespace Robot;
using namespace Base;
//using namespace KDL;


TYPESYSTEM_SOURCE(Robot::Trajectory , Base::Persistence);

Trajectory::Trajectory()
:pcTrajectory(0)
{

}

Trajectory::~Trajectory()
{
    for(std::vector<Waypoint*>::iterator it = vpcWaypoints.begin();it!=vpcWaypoints.end();++it)
        delete ( *it );
}


double Trajectory::getLength(void)
{
    return 0;
}

Placement Trajectory::getPosition(double time)
{
    return Placement();
}


void Trajectory::generateTrajectory(void)
{
    if(pcTrajectory) delete (pcTrajectory);

    pcTrajectory = new KDL::Trajectory_Composite();

}

void Trajectory::addWaypoint(const Waypoint &WPnt)
{
    Waypoint *tmp = new Waypoint(WPnt);
    vpcWaypoints.push_back(tmp);
}




unsigned int Trajectory::getMemSize (void) const
{
	return 0;
}

void Trajectory::Save (Writer &/*writer*/) const
{
}

void Trajectory::Restore(XMLReader &/*reader*/)
{
}




 