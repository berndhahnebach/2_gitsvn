/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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


#ifndef INSPECTION_FEATURE_H
#define INSPECTION_FEATURE_H

#include <App/DocumentObject.h>
#include <App/PropertyLinks.h>
#include <App/DocumentObjectGroup.h>

#include <Mod/Mesh/App/Core/Iterator.h>
#include <Mod/Points/App/Points.h>

class TopoDS_Shape;
class BRepExtrema_DistShapeShape;

namespace MeshCore {
class MeshKernel;
class MeshFacetGrid;
}

namespace Points { class PointsGrid; }
namespace Part { class TopoShape; }

namespace Inspection
{

/** Delivers the number of points to be checked and returns the appropriate point to an index. */
class InspectionAppExport InspectActualGeometry
{
public:
    InspectActualGeometry() {}
    virtual ~InspectActualGeometry() {}
    /// Number of points to be checked
    virtual unsigned long countPoints() const = 0;
    virtual Base::Vector3f getPoint(unsigned long) = 0;
};

class InspectionAppExport InspectActualMesh : public InspectActualGeometry
{
public:
    InspectActualMesh( const MeshCore::MeshKernel& rMesh );
    ~InspectActualMesh();
    virtual unsigned long countPoints() const;
    virtual Base::Vector3f getPoint(unsigned long);

private:
    MeshCore::MeshPointIterator _iter;
    unsigned long _count;
};

class InspectionAppExport InspectActualPoints : public InspectActualGeometry
{
public:
    InspectActualPoints(const Points::PointKernel&);
    virtual unsigned long countPoints() const;
    virtual Base::Vector3f getPoint(unsigned long);

private:
    const Points::PointKernel& _rKernel;
};

class InspectionAppExport InspectActualShape : public InspectActualGeometry
{
public:
    InspectActualShape(const Part::TopoShape&);
    virtual unsigned long countPoints() const;
    virtual Base::Vector3f getPoint(unsigned long);

private:
    const Part::TopoShape& _rShape;
    std::vector<Base::Vector3d> points;
};

/** Calculates the shortest distance of the underlying geometry to a given point. */
class InspectionAppExport InspectNominalGeometry
{
public:
    InspectNominalGeometry() {}
    virtual ~InspectNominalGeometry() {}
    virtual float getDistance(const Base::Vector3f&) = 0;
};

class InspectionAppExport InspectNominalMesh : public InspectNominalGeometry
{
public:
    InspectNominalMesh(const MeshCore::MeshKernel& rMesh, float offset);
    ~InspectNominalMesh();
    virtual float getDistance(const Base::Vector3f&);

private:
    MeshCore::MeshFacetIterator _iter;
    MeshCore::MeshFacetGrid* _pGrid;
    Base::BoundBox3f _box;
};

class InspectionAppExport InspectNominalFastMesh : public InspectNominalGeometry
{
public:
    InspectNominalFastMesh(const MeshCore::MeshKernel& rMesh, float offset);
    ~InspectNominalFastMesh();
    virtual float getDistance(const Base::Vector3f&);

protected:
    MeshCore::MeshFacetIterator _iter;
    MeshCore::MeshFacetGrid* _pGrid;
    Base::BoundBox3f _box;
    unsigned long max_level;
};

class InspectionAppExport InspectNominalPoints : public InspectNominalGeometry
{
public:
    InspectNominalPoints(const Points::PointKernel&, float offset);
    ~InspectNominalPoints();
    virtual float getDistance(const Base::Vector3f&);

private:
    const Points::PointKernel& _rKernel;
    Points::PointsGrid* _pGrid;
};

class InspectionAppExport InspectNominalShape : public InspectNominalGeometry
{
public:
    InspectNominalShape(const TopoDS_Shape&, float offset);
    ~InspectNominalShape();
    virtual float getDistance(const Base::Vector3f&);

private:
    BRepExtrema_DistShapeShape* distss;
    const TopoDS_Shape& _rShape;
};

// ----------------------------------------------------------------

/** The inspection feature.
 * \author Werner Mayer
 */
class InspectionAppExport Feature : public App::DocumentObject
{
    PROPERTY_HEADER(Inspection::Feature);

public:
    /// Constructor
    Feature(void);
    virtual ~Feature();

    /** @name Properties */
    //@{
    App::PropertyFloat     SearchRadius;
    App::PropertyFloat     Thickness;
    App::PropertyLink      Actual;
    App::PropertyLinkList  Nominals;
    App::PropertyFloatList Distances;
    //@}

    /** @name Actions */
    //@{
    short mustExecute() const;
    /// recalculate the Feature
    App::DocumentObjectExecReturn* execute(void);
    //@}

    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const 
    { return "InspectionGui::ViewProviderInspection"; }
};

class InspectionAppExport Group : public App::DocumentObjectGroup
{
    PROPERTY_HEADER(Inspection::Group);

public:
    /// Constructor
    Group(void);
    virtual ~Group();

    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const 
    { return "InspectionGui::ViewProviderInspectionGroup"; }
};

} //namespace Inspection


#endif // INSPECTION_FEATURE_H