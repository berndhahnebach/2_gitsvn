/***************************************************************************
 *   Copyright (c) 2008 J�rgen Riegel (juergen.riegel@web.de)              *
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


#ifndef ROBOT_ViewProviderFemMesh_H
#define ROBOT_ViewProviderFemMesh_H

#include <Inventor/VRMLnodes/SoVRMLTransform.h>
#include <Gui/ViewProviderGeometryObject.h>
#include <Gui/SoFCSelection.h>

class SoDragger;
class SoJackDragger;
class SoCoordinate3;
class SoDrawStyle;  
class SoLineSet; 

namespace FemGui
{

class FemGuiExport ViewProviderFemMesh : public Gui::ViewProviderGeometryObject
{
    PROPERTY_HEADER(FemGui::ViewProviderFemMesh);

public:
    /// constructor.
    ViewProviderFemMesh();

    /// destructor.
    ~ViewProviderFemMesh();

    void attach(App::DocumentObject *pcObject);
    void setDisplayMode(const char* ModeName);
    std::vector<std::string> getDisplayModes() const;
    void updateData(const App::Property*);

protected:
 
    Gui::SoFCSelection    * pcFemMeshRoot;
    SoCoordinate3         * pcCoords;
    SoDrawStyle           * pcDrawStyle;
    SoLineSet             * pcLines;

 };

} //namespace FemGui


#endif // ROBOT_VIEWPROVIDERROBOTOBJECT_H