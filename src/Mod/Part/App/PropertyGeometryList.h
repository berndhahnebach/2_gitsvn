/***************************************************************************
 *   Copyright (c) J�rgen Riegel          (juergen.riegel@web.de) 2010     *
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


#ifndef APP_PropertyGeometryList_H
#define APP_PropertyGeometryList_H

// Std. configurations


#include <vector>
#include <string>
#include <App/Property.h>
#include "Geometry.h"

namespace Base {
class Writer;
}

namespace Part
{
class Geometry;

class AppPartExport PropertyGeometryList: public App::PropertyLists
{
    TYPESYSTEM_HEADER();

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyGeometryList();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    virtual ~PropertyGeometryList();

    virtual void setSize(int newSize);
    virtual int getSize(void) const;

    /** Sets the property
     */
    void setValue(const Geometry*);
    void setValues(const std::vector<Geometry*>&);

    /// index operator
    const Geometry *operator[] (const int idx) const {
        return _lValueList.operator[] (idx);
    }


    void  set1Value (const int idx, Geometry* value) {
        _lValueList.operator[] (idx) = value->clone();
    }

    const std::vector<Geometry*> &getValues(void) const {
        return _lValueList;
    }

    virtual PyObject *getPyObject(void);
    virtual void setPyObject(PyObject *);

    virtual void Save (Base::Writer &writer) const;
    virtual void Restore(Base::XMLReader &reader);

    virtual Property *Copy(void) const;
    virtual void Paste(const Property &from);

    virtual unsigned int getMemSize (void) const;

private:
    std::vector<Geometry*> _lValueList;
};

} // namespace Part


#endif // APP_PropertyGeometryList_H