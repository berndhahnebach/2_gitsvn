/***************************************************************************
 *   Copyright (c) J�rgen Riegel          (juergen.riegel@web.de) 2009     *
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


#ifndef FEM_FemMesh_H
#define FEM_FemMesh_H



#include <App/ComplexGeoData.h>
#include <Base/Placement.h>

#include <vector>

class SMESH_Mesh;

namespace Fem
{


/** The representation of a FemMesh
 */
class AppFemExport FemMesh : public Data::ComplexGeoData
{
    TYPESYSTEM_HEADER();

public:
    FemMesh();
    FemMesh(const FemMesh&);
    ~FemMesh();

    FemMesh &operator=(const FemMesh&);

	// from base class
    virtual unsigned int getMemSize (void) const;
	virtual void Save (Base::Writer &/*writer*/) const;
    virtual void Restore(Base::XMLReader &/*reader*/);
    void SaveDocFile (Base::Writer &writer) const;
    void RestoreDocFile(Base::Reader &reader);

    /** @name Subelement management */
    //@{
    /** Sub type list
     *  List of different subelement types
     *  it is NOT a list of the subelements itself
     */
    virtual std::vector<const char*> getElementTypes(void) const;
    /// get the subelement by type and number
    virtual Data::Segment* getSubElement(const char* Type, unsigned long) const;
    //@}

    /** @name Placement control */
    //@{
    /// set the transformation 
    void setTransform(const Base::Matrix4D& rclTrf);
    /// get the transformation 
    Base::Matrix4D getTransform(void) const;
    /// Bound box from the shape
    Base::BoundBox3d getBoundBox(void)const;
    //@}


    /// import from files
    void read(const char *FileName);
    void write(const char *FileName);


    SMESH_Mesh *myMesh;

};

} //namespace Part


#endif // PART_TOPOSHAPE_H