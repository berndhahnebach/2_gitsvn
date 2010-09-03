/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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
# include <QAction>
# include <QMenu>
# include <Standard_math.hxx>
# include <Inventor/actions/SoSearchAction.h>
# include <Inventor/draggers/SoDragger.h>
# include <Inventor/nodes/SoCoordinate3.h>
# include <Inventor/nodes/SoFaceSet.h>
# include <Inventor/nodes/SoMaterial.h>
# include <Inventor/nodes/SoSeparator.h>
# include <Inventor/manips/SoCenterballManip.h>
#endif

#include <Mod/Part/App/FeatureMirroring.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include "ViewProviderMirror.h"

using namespace PartGui;


PROPERTY_SOURCE(PartGui::ViewProviderMirror, PartGui::ViewProviderPart)

ViewProviderMirror::ViewProviderMirror()
{
    sPixmap = "Part_Mirror";
    pcEditNode = new SoSeparator();
    pcEditNode->ref();
}

ViewProviderMirror::~ViewProviderMirror()
{
    pcEditNode->unref();
}

void ViewProviderMirror::setupContextMenu(QMenu* menu, QObject* receiver, const char* member)
{
    QAction* act;
    act = menu->addAction(QObject::tr("Edit mirror plane"), receiver, member);
    act->setData(QVariant((int)ViewProvider::Default));
    act = menu->addAction(QObject::tr("Transform"), receiver, member);
    act->setData(QVariant((int)ViewProvider::Transform));
}

bool ViewProviderMirror::setEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        // get the properties from the mirror feature
        Part::Mirroring* mf = static_cast<Part::Mirroring*>(getObject());
        Base::BoundBox3d bbox = mf->Shape.getBoundingBox();
        float len = (float)bbox.CalcDiagonalLength();
        Base::Vector3f base = mf->Base.getValue();
        Base::Vector3f norm = mf->Normal.getValue();
        Base::Vector3d cent = bbox.CalcCenter();
        Base::Vector3f cbox((float)cent.x,(float)cent.y,(float)cent.z);
        base = cbox.ProjToPlane(base, norm);

        // setup the graph for editing the mirror plane
        SoTransform* trans = new SoTransform;
        SbRotation rot(SbVec3f(0,0,1), SbVec3f(norm.x,norm.y,norm.z));
        trans->rotation.setValue(rot);
        trans->translation.setValue(base.x,base.y,base.z);
        trans->center.setValue(0.0f,0.0f,0.0f);

        SoMaterial* color = new SoMaterial();
        color->diffuseColor.setValue(0,0,1);
        color->transparency.setValue(0.5);
        SoCoordinate3* points = new SoCoordinate3();
        points->point.setNum(4);
        points->point.set1Value(0, -len/2,-len/2,0);
        points->point.set1Value(1,  len/2,-len/2,0);
        points->point.set1Value(2,  len/2, len/2,0);
        points->point.set1Value(3, -len/2, len/2,0);
        SoFaceSet* face = new SoFaceSet();
        pcEditNode->addChild(trans);
        pcEditNode->addChild(color);
        pcEditNode->addChild(points);
        pcEditNode->addChild(face);

        // Now we replace the SoTransform node by a manipulator
        // Note: Even SoCenterballManip inherits from SoTransform
        // we cannot use it directly (in above code) because the
        // translation and center fields are overridden.
        SoSearchAction sa;
        sa.setInterest(SoSearchAction::FIRST);
        sa.setSearchingAll(FALSE);
        sa.setNode(trans);
        sa.apply(pcEditNode);
        SoPath * path = sa.getPath();
        if (path) {
            SoCenterballManip * manip = new SoCenterballManip;
            manip->replaceNode(path);

            SoDragger* dragger = manip->getDragger();
            dragger->addStartCallback(dragStartCallback, this);
            dragger->addFinishCallback(dragFinishCallback, this);
            dragger->addMotionCallback(dragMotionCallback, this);
        }
        pcRoot->addChild(pcEditNode);
    }
    else {
        ViewProviderPart::setEdit(ModNum);
    }

    return true;
}

void ViewProviderMirror::unsetEdit(int ModNum)
{
    if (ModNum == ViewProvider::Default) {
        SoCenterballManip* manip = static_cast<SoCenterballManip *>(pcEditNode->getChild(0));

        SbVec3f move = manip->translation.getValue();
        SbVec3f center = manip->center.getValue();
        SbRotation rot = manip->rotation.getValue();

        // get the whole translation
        move += center;
        rot.multVec(center,center);
        move -= center;

        // the new axis of the plane
        SbVec3f norm(0,0,1);
        rot.multVec(norm,norm);

        // apply the new values
        Part::Mirroring* mf = static_cast<Part::Mirroring*>(getObject());
        mf->Base.setValue(move[0],move[1],move[2]);
        mf->Normal.setValue(norm[0],norm[1],norm[2]);

        pcRoot->removeChild(pcEditNode);
        pcEditNode->removeAllChildren();
    }
    else {
        ViewProviderPart::unsetEdit(ModNum);
    }
}

void ViewProviderMirror::dragStartCallback(void *data, SoDragger *)
{
    // This is called when a manipulator is about to manipulating
    Gui::Application::Instance->activeDocument()->openCommand("Edit Mirror");
}

void ViewProviderMirror::dragFinishCallback(void *data, SoDragger *)
{
    // This is called when a manipulator has done manipulating
    Gui::Application::Instance->activeDocument()->commitCommand();
}

void ViewProviderMirror::dragMotionCallback(void *data, SoDragger *drag)
{
    ViewProviderMirror* that = reinterpret_cast<ViewProviderMirror*>(data);
    const SbMatrix& mat = drag->getMotionMatrix();
    // the new axis of the plane
    SbRotation rot(mat);
    SbVec3f norm(0,0,1);
    rot.multVec(norm,norm);
    Part::Mirroring* mf = static_cast<Part::Mirroring*>(that->getObject());
    mf->Base.setValue(mat[3][0],mat[3][1],mat[3][2]);
    mf->Normal.setValue(norm[0],norm[1],norm[2]);
}