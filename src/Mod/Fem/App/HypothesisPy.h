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

#ifndef FEM_HYPOTHESISPY_H
#define FEM_HYPOTHESISPY_H

#include <CXX/Extensions.hxx>
#include <boost/shared_ptr.hpp>

class SMESH_Hypothesis;
class SMESH_Gen;

namespace Fem {

class HypothesisPy : public Py::PythonExtension<HypothesisPy>
{
public:
    typedef Py::PythonExtension<HypothesisPy> HypothesisPyBase;
    HypothesisPy(boost::shared_ptr<SMESH_Hypothesis>);
    virtual ~HypothesisPy();
    boost::shared_ptr<SMESH_Hypothesis> getHypothesis() const
    { return hyp; }

private:
    boost::shared_ptr<SMESH_Hypothesis> hyp;
};

typedef Py::ExtensionObject<HypothesisPy> Hypothesis;

template <class T>
class SMESH_HypothesisPy : public Py::PythonExtension<T>
{
public:
    typedef SMESH_HypothesisPy<T> SMESH_HypothesisPyBase;
    static void init_type(void);    // announce properties and methods

    SMESH_HypothesisPy(SMESH_Hypothesis*);
    virtual ~SMESH_HypothesisPy();

    Py::Object getattr(const char *name);
    Py::Object repr();
    Py::Object getLibName(const Py::Tuple& args);
    Py::Object setLibName(const Py::Tuple& args);
    Py::Object setParameters(const Py::Tuple& args);
    Py::Object getParameters(const Py::Tuple& args);
    Py::Object setLastParameters(const Py::Tuple& args);
    Py::Object getLastParameters(const Py::Tuple& args);
    Py::Object clearParameters(const Py::Tuple& args);
    Py::Object isAuxiliary(const Py::Tuple& args);
    Py::Object setParametersByMesh(const Py::Tuple& args);

    boost::shared_ptr<SMESH_Hypothesis> getHypothesis() const
    { return hyp; }

protected:
    template<typename type>
    type* hypothesis() const
    { return static_cast<type*>(hyp.get()); }

private:
    static PyObject *PyMake(struct _typeobject *, PyObject *, PyObject *);

private:
    boost::shared_ptr<SMESH_Hypothesis> hyp;
};

class StdMeshers_Arithmetic1DPy : public SMESH_HypothesisPy<StdMeshers_Arithmetic1DPy>
{
public:
    static void init_type(void);
    StdMeshers_Arithmetic1DPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_Arithmetic1DPy();

    Py::Object setLength(const Py::Tuple& args);
    Py::Object getLength(const Py::Tuple& args);
};

class StdMeshers_AutomaticLengthPy : public SMESH_HypothesisPy<StdMeshers_AutomaticLengthPy>
{
public:
    static void init_type(void);
    StdMeshers_AutomaticLengthPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_AutomaticLengthPy();

    Py::Object setFineness(const Py::Tuple& args);
    Py::Object getFineness(const Py::Tuple& args);
    Py::Object getLength(const Py::Tuple& args);
};

class StdMeshers_NotConformAllowedPy : public SMESH_HypothesisPy<StdMeshers_NotConformAllowedPy>
{
public:
    static void init_type(void);
    StdMeshers_NotConformAllowedPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_NotConformAllowedPy();
};

class StdMeshers_MaxLengthPy : public SMESH_HypothesisPy<StdMeshers_MaxLengthPy>
{
public:
    static void init_type(void);
    StdMeshers_MaxLengthPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_MaxLengthPy();

    Py::Object setLength(const Py::Tuple& args);
    Py::Object getLength(const Py::Tuple& args);
    Py::Object havePreestimatedLength(const Py::Tuple& args);
    Py::Object getPreestimatedLength(const Py::Tuple& args);
    Py::Object setPreestimatedLength(const Py::Tuple& args);
    Py::Object setUsePreestimatedLength(const Py::Tuple& args);
    Py::Object getUsePreestimatedLength(const Py::Tuple& args);
};

class StdMeshers_LocalLengthPy : public SMESH_HypothesisPy<StdMeshers_LocalLengthPy>
{
public:
    static void init_type(void);
    StdMeshers_LocalLengthPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_LocalLengthPy();

    Py::Object setLength(const Py::Tuple& args);
    Py::Object getLength(const Py::Tuple& args);
    Py::Object setPrecision(const Py::Tuple& args);
    Py::Object getPrecision(const Py::Tuple& args);
};

class StdMeshers_MaxElementAreaPy : public SMESH_HypothesisPy<StdMeshers_MaxElementAreaPy>
{
public:
    static void init_type(void);
    StdMeshers_MaxElementAreaPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_MaxElementAreaPy();

    Py::Object setMaxArea(const Py::Tuple& args);
    Py::Object getMaxArea(const Py::Tuple& args);
};

class StdMeshers_QuadranglePreferencePy : public SMESH_HypothesisPy<StdMeshers_QuadranglePreferencePy>
{
public:
    static void init_type(void);
    StdMeshers_QuadranglePreferencePy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_QuadranglePreferencePy();
};

class StdMeshers_Quadrangle_2DPy : public SMESH_HypothesisPy<StdMeshers_Quadrangle_2DPy>
{
public:
    static void init_type(void);
    StdMeshers_Quadrangle_2DPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_Quadrangle_2DPy();
};

class StdMeshers_Regular_1DPy : public SMESH_HypothesisPy<StdMeshers_Regular_1DPy>
{
public:
    static void init_type(void);
    StdMeshers_Regular_1DPy(int hypId, int studyId, SMESH_Gen* gen);
    ~StdMeshers_Regular_1DPy();
};

} // namespace Fem

#endif // FEM_HYPOTHESISPY_H