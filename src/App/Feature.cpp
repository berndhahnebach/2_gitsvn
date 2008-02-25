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
# include <sstream>
#endif

#include <Base/PyObjectBase.h>
#include <Base/Console.h>
#include <Base/Exception.h>
#include <Base/Vector3D.h>
#include <Base/Matrix.h>
using Base::Console;

#include "Document.h"
#include "Feature.h"
#include "FeaturePy.h"
#include "Property.h"

#define new DEBUG_CLIENTBLOCK
using namespace App;

using std::vector;
using std::string;
using std::map;

PROPERTY_SOURCE_ABSTRACT(App::AbstractFeature, App::DocumentObject)


//===========================================================================
// Feature
//===========================================================================

const char* FeatEnums[]= {"Valid","New","Inactive","Recompute","Error",NULL};

AbstractFeature::AbstractFeature(void)
        : _execute(false)
{
    ADD_PROPERTY_TYPE(status,(1),"Base",Prop_None,"Current status of the Feature");
    status.setEnums(FeatEnums);
}

AbstractFeature::~AbstractFeature(void)
{
}

PyObject *AbstractFeature::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject.set(new FeaturePy(this),true);
    }
    return Py::new_reference_to(PythonObject);
}

void AbstractFeature::onChanged(const Property* prop)
{
    // call father for Undo/Redo...
    DocumentObject::onChanged(prop);

    // Ignore some properties
    if ( prop == &status )
        return;
    else if ( prop == &Label )
        return;
    //touchPropertyTime.setToActual();
}

short AbstractFeature::mustExecute(void) const
{
    // If the object's label is modified:
    if (getStatus() != Valid && getStatus()!= Inactive)
        return 1;
    //FIXME: The setModified() method is a workaround for the problems with the time stamp.
    //E.g. when a property has changed then the feature itself has changed. If the recomputation takes place
    //immediately and is finished very fast then it could happen that the OS returns the same time stamp for both
    //events. And the other way round a property has changed immediately after a recomputation of the feature.
    //In both cases the time stamp doesn't work as expected. Using a boolean instead solves the problem.
    return 0;
//  if ( touchTime <= touchPropertyTime )
//    return true;
//
//  return false;

}

#if 0
void AbstractFeature::recompute(void)
{
    _pDoc->recomputeFeature(this);
}
#endif
#if 0
const char* AbstractFeature::getStatusString(void) const
{
    switch (status.getValue()) {
    case Valid:
        return "Valid";
    case New:
        return "New";
    case Inactive:
        return "Inactive";
    case Recompute:
        return "Recompute";
    case Error:
        return "Error";
    default:
        return "Unknown";
    }
}
#endif
#if 0
void AbstractFeature::setError(const char* pMsg,...)
{
    // temp buffer
    size_t format_len = strlen(pMsg)+4024;
    char* format = (char*) malloc(format_len);

    va_list namelessVars;
    va_start(namelessVars, pMsg);  // Get the "..." vars
    vsnprintf(format, format_len, pMsg, namelessVars);
    va_end(namelessVars);

    /*_eStatus = Error;*/
    status.setValue(Error);
    _cErrorMessage = format;
}
#endif
