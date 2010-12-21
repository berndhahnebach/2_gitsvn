/***************************************************************************
 *   Copyright (c) 2010 J�rgen Riegel (juergen.riegel@web.de)              *
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

#include "Edge2TracObject.h"
//#include <App/DocumentObjectPy.h>
//#include <Base/Placement.h>

using namespace Robot;
using namespace App;

PROPERTY_SOURCE(Robot::Edge2TracObject, Robot::TrajectoryObject)


Edge2TracObject::Edge2TracObject()
{

    ADD_PROPERTY_TYPE( Source,      (0)   , "Edge2Trac",Prop_None,"Edges to generate the Trajectory");
    ADD_PROPERTY_TYPE( SegValue,    (0.5), "Edge2Trac",Prop_None,"Max deviation from original geometry");

}

Edge2TracObject::~Edge2TracObject()
{
}

short Edge2TracObject::mustExecute(void) const
{
    return 0;
}

void Edge2TracObject::onChanged(const Property* prop)
{
 
    App::GeoFeature::onChanged(prop);
}