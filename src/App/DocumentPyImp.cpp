/***************************************************************************
 *   Copyright (c) J�rgen Riegel          (juergen.riegel@web.de) 2007     *
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

#include "Document.h"
#include <Base/FileInfo.h>
#include <Base/PyTools.h>
#include "DocumentObject.h"
#include "DocumentObjectPy.h"

// inclusion of the generated files (generated By DocumentPy.xml)
#include "DocumentPy.h"
#include "DocumentPy.cpp"

using namespace App;


// returns a string which represent the object e.g. when printed in python
const char *DocumentPy::representation(void) const
{
    std::stringstream str;
    str << "<Document object at " << getDocumentPtr() << ">";

    // Note: As the return type is 'const char*' we cannot create a temporary char array neither on the stack because the array would be freed
    // when leaving the scope nor on the heap because we would have a memory leak.
    // So we use a static array that is used by all instances of this class. This, however, is not a problem as long as we only
    // use this method in _repr().
    static std::string buf;
    buf = str.str();
    return buf.c_str();
}

PyObject*  DocumentPy::save(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    if (!getDocumentPtr()->save()) {
        PyErr_Format(PyExc_ValueError, "Object attribute 'FileName' is not set");
        return NULL;
    }

    const char* filename = getDocumentPtr()->FileName.getValue();
    Base::FileInfo fi(filename);
    if (!fi.isReadable()) {
        PyErr_Format(PyExc_IOError, "No such file or directory: '%s'", filename);
        return NULL;
    }

    Py_Return;
}

PyObject*  DocumentPy::restore(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    const char* filename = getDocumentPtr()->FileName.getValue();
    if (!filename || *filename == '\0') {
        PyErr_Format(PyExc_ValueError, "Object attribute 'FileName' is not set");
        return NULL;
    }
    Base::FileInfo fi(filename);
    if (!fi.isReadable()) {
        PyErr_Format(PyExc_IOError, "No such file or directory: '%s'", filename);
        return NULL;
    }
    try {
        getDocumentPtr()->restore();
    } catch (...) {
        PyErr_Format(PyExc_IOError, "Reading from file '%s' failed", filename);
        return NULL;
    }
    Py_Return;
}

PyObject*  DocumentPy::addObject(PyObject *args)
{
    char *sType,*sName=0;
    if (!PyArg_ParseTuple(args, "s|s", &sType,&sName))     // convert args: Python->C
        return NULL;                                         // NULL triggers exception 

    DocumentObject *pcFtr;

    pcFtr = getDocumentPtr()->addObject(sType,sName);

    if(pcFtr)
        return pcFtr->getPyObject();
    else
    {
        std::stringstream str;
        str << "No document object found of type '" << sType << "'" << std::ends;
        throw Py::Exception(PyExc_Exception,str.str());
    }
}

PyObject*  DocumentPy::removeObject(PyObject *args)
{
    char *sName;
    if (!PyArg_ParseTuple(args, "s",&sName))     // convert args: Python->C
        return NULL;                             // NULL triggers exception


    DocumentObject *pcFtr = getDocumentPtr()->getObject(sName);
    if(pcFtr) {
        getDocumentPtr()->remObject( sName );
        Py_Return;
    } else {
        std::stringstream str;
        str << "No document object found with name '" << sName << "'" << std::ends;
        throw Py::Exception(PyExc_Exception,str.str());
    }
}

PyObject*  DocumentPy::copyObject(PyObject *args)
{
    PyObject *obj, *rec=0;
    if (!PyArg_ParseTuple(args, "O!|O!",&(DocumentObjectPy::Type),&obj,&PyBool_Type,&rec))
        return NULL;    // NULL triggers exception

    DocumentObjectPy* docObj = static_cast<DocumentObjectPy*>(obj);
    DocumentObject* copy = getDocumentPtr()->copyObject(docObj->getDocumentObjectPtr(), rec==Py_True);
    if (copy) {
        return copy->getPyObject();
    }
    else {
        std::string str("Failed to copy the object");
        throw Py::Exception(PyExc_Exception,str);
    }
}

PyObject*  DocumentPy::moveObject(PyObject *args)
{
    PyObject *obj, *rec=0;
    if (!PyArg_ParseTuple(args, "O!|O!",&(DocumentObjectPy::Type),&obj,&PyBool_Type,&rec))
        return NULL;    // NULL triggers exception

    DocumentObjectPy* docObj = static_cast<DocumentObjectPy*>(obj);
    DocumentObject* move = getDocumentPtr()->moveObject(docObj->getDocumentObjectPtr(), rec==Py_True);
    if (move) {
        return move->getPyObject();
    }
    else {
        std::string str("Failed to move the object");
        throw Py::Exception(PyExc_Exception,str);
    }
}

PyObject*  DocumentPy::openTransaction(PyObject *args)
{
    char *pstr=0;
    if (!PyArg_ParseTuple(args, "|s", &pstr))     // convert args: Python->C 
        return NULL;                             // NULL triggers exception 

    getDocumentPtr()->openTransaction(pstr); 
    Py_Return; 
}

PyObject*  DocumentPy::abortTransaction(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    getDocumentPtr()->abortTransaction();
    Py_Return;
}

PyObject*  DocumentPy::commitTransaction(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    getDocumentPtr()->commitTransaction();
    Py_Return;
}

PyObject*  DocumentPy::undo(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    if (getDocumentPtr()->getAvailableUndos())
        getDocumentPtr()->undo();
    Py_Return;
}

PyObject*  DocumentPy::redo(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    if (getDocumentPtr()->getAvailableRedos())
        getDocumentPtr()->redo();
    Py_Return;
}

PyObject*  DocumentPy::clearUndos(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    getDocumentPtr()->clearUndos();
    Py_Return;
}

PyObject*  DocumentPy::recompute(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception 
    getDocumentPtr()->recompute();
    Py_Return;
}

PyObject*  DocumentPy::getObject(PyObject *args)
{
    char *sName;
    if (!PyArg_ParseTuple(args, "s",&sName))     // convert args: Python->C 
        return NULL;                             // NULL triggers exception 

    DocumentObject *pcFtr = getDocumentPtr()->getObject(sName);
    if(pcFtr)
        return pcFtr->getPyObject();
    else
        Py_Return;
}

PyObject*  DocumentPy::findObjects(PyObject *args)
{
    char *sType="App::DocumentObject", *sName=0;
    if (!PyArg_ParseTuple(args, "|ss",&sType, &sName))     // convert args: Python->C 
        return NULL;                                      // NULL triggers exception 

    Base::Type type = Base::Type::fromName(sType);
    if (type == Base::Type::badType()) {
        PyErr_Format(PyExc_Exception, "'%s' is not a valid type", sType);
        return NULL;
    }
    
    if (!type.isDerivedFrom(App::DocumentObject::getClassTypeId())) {
        PyErr_Format(PyExc_Exception, "Type '%s' does not inherit from 'App::DocumentObject'", sType);
        return NULL;
    }
    
    std::vector<DocumentObject*> objs = getDocumentPtr()->getObjectsOfType(type);
    std::vector<DocumentObject*> res;
    for (std::vector<DocumentObject*>::const_iterator It = objs.begin();It != objs.end();++It) {
        if (sName) {
            std::string name = (*It)->getNameInDocument();
            if (name.find(sName) == std::string::npos)
                continue;
        }

        res.push_back(*It);
    }

    Py_ssize_t index=0;
    PyObject* list = PyList_New((Py_ssize_t)res.size()); 
    for (std::vector<DocumentObject*>::const_iterator It = res.begin();It != res.end();++It, index++)
        PyList_SetItem(list, index, (*It)->getPyObject());
    return list;
}

Py::Object DocumentPy::getActiveObject(void) const
{
    DocumentObject *pcFtr = getDocumentPtr()->getActiveObject();
    if(pcFtr)
        return Py::Object(pcFtr->getPyObject(), true);
    return Py::None();
}

PyObject*  DocumentPy::supportedTypes(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception
    
    std::vector<Base::Type> ary;
    Base::Type::getAllDerivedFrom(App::DocumentObject::getClassTypeId(), ary);
    Py::List res;
    for (std::vector<Base::Type>::iterator it = ary.begin(); it != ary.end(); ++it)
        res.append(Py::String(it->getName()));
    return Py::new_reference_to(res);
}

void  DocumentPy::setActiveObject(Py::Object /*arg*/)
{
    throw Py::AttributeError("'Document' object attribute 'ActiveObject' is read-only");
}

Py::List DocumentPy::getObjects(void) const 
{
    std::vector<DocumentObject*> objs = getDocumentPtr()->getObjects();
    Py::List res;

    for (std::vector<DocumentObject*>::const_iterator It = objs.begin();It != objs.end();++It)
        //Note: Here we must force the Py::Object to own this Python object as getPyObject() increments the counter
        res.append(Py::Object((*It)->getPyObject(), true));

    return res;
}

Py::Int DocumentPy::getUndoMode(void) const
{
    return Py::Int(getDocumentPtr()->getUndoMode());
}

void  DocumentPy::setUndoMode(Py::Int arg)
{
    getDocumentPtr()->setUndoMode(arg); 
}

Py::Int DocumentPy::getUndoRedoMemSize(void) const
{
    return Py::Int((long)getDocumentPtr()->getUndoMemSize());
}

Py::Int DocumentPy::getUndoCount(void) const
{
    return Py::Int((long)getDocumentPtr()->getAvailableUndos());
}

Py::Int DocumentPy::getRedoCount(void) const
{
    return Py::Int((long)getDocumentPtr()->getAvailableRedos());
}

Py::List DocumentPy::getUndoNames(void) const
{
    std::vector<std::string> vList = getDocumentPtr()->getAvailableUndoNames();
    Py::List res;

    for (std::vector<std::string>::const_iterator It = vList.begin();It!=vList.end();++It)
        res.append(Py::String(*It));

    return res;
}

Py::List DocumentPy::getRedoNames(void) const
{
    std::vector<std::string> vList = getDocumentPtr()->getAvailableRedoNames();
    Py::List res;

    for (std::vector<std::string>::const_iterator It = vList.begin();It!=vList.end();++It)
        res.append(Py::String(*It));

    return res;
}

Py::String  DocumentPy::getDependencyGraph(void) const
{
    std::stringstream out;
    getDocumentPtr()->writeDependencyGraphViz(out);
    return Py::String(out.str());
}

Py::String DocumentPy::getName(void) const
{
    return Py::String(getDocumentPtr()->getName());
}

PyObject* DocumentPy::getTempFileName(PyObject *args)
{
    PyObject *value;
    if (!PyArg_ParseTuple(args, "O",&value))
        return NULL;    // NULL triggers exception

    std::string string;
    if (PyUnicode_Check(value)) {
        PyObject* unicode = PyUnicode_AsUTF8String(value);
        string = PyString_AsString(unicode);
        Py_DECREF(unicode);
    }
    else if (PyString_Check(value)) {
        string = PyString_AsString(value);
    }
    else {
        std::string error = std::string("type must be a string!");
        error += value->ob_type->tp_name;
        throw Py::TypeError(error);
    }

    // search for a temp file name in the document transient directory 
    Base::FileInfo fileName(Base::FileInfo::getTempFileName
        (string.c_str(),getDocumentPtr()->TransientDir.getValue()));
    // delete the created file, we need only the name...
    fileName.deleteFile();

    PyObject *p = PyUnicode_DecodeUTF8(fileName.filePath().c_str(),fileName.filePath().size(),0);
    if (!p) throw Base::Exception("UTF8 conversion failure at PropertyString::getPyObject()");
    return p;
}

PyObject *DocumentPy::getCustomAttributes(const char* attr) const
{
    // Note: Here we want to return only a document object if its
    // name matches 'attr'. However, it is possible to have an object
    // with the same name as an attribute. If so, we return 0 as other-
    // wise it wouldn't be possible to address this attribute any more.
    // The object must then be addressed by the getObject() method directly.
    App::Property* prop = getPropertyContainerPtr()->getPropertyByName(attr);
    if (prop) return 0;
    if (this->ob_type->tp_dict == NULL) {
        if (PyType_Ready(this->ob_type) < 0)
            return 0;
    }
    PyObject* item = PyDict_GetItemString(this->ob_type->tp_dict, attr);
    if (item) return 0;
    // search for an object with this name
    DocumentObject* obj = getDocumentPtr()->getObject(attr);
    return (obj ? obj->getPyObject() : 0);
}

int DocumentPy::setCustomAttributes(const char* attr, PyObject *)
{
    // Note: Here we want to return only a document object if its
    // name matches 'attr'. However, it is possible to have an object
    // with the same name as an attribute. If so, we return 0 as other-
    // wise it wouldn't be possible to address this attribute any more.
    // The object must then be addressed by the getObject() method directly.
    App::Property* prop = getPropertyContainerPtr()->getPropertyByName(attr);
    if (prop) return 0;
    if (this->ob_type->tp_dict == NULL) {
        if (PyType_Ready(this->ob_type) < 0)
            return 0;
    }
    PyObject* item = PyDict_GetItemString(this->ob_type->tp_dict, attr);
    if (item) return 0;
    DocumentObject* obj = getDocumentPtr()->getObject(attr);
    if (obj)
    {
        std::stringstream str;
        str << "'Document' object attribute '" << attr 
            << "' must not be set this way" << std::ends;
        throw Py::AttributeError(str.str());
    }
    
    return 0;
}
