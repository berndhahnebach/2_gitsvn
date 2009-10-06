
#include "PreCompiled.h"

#include <Base/VectorPy.h>
#include <Base/PlacementPy.h>
#include "Mod/Robot/App/Trajectory.h"

// inclusion of the generated files (generated out of TrajectoryPy.xml)
#include "TrajectoryPy.h"
#include "TrajectoryPy.cpp"

#include "WaypointPy.h"

using namespace Robot;

// returns a string which represents the object e.g. when printed in python
std::string TrajectoryPy::representation(void) const
{
    std::stringstream str;
    str.precision(5);
    str << "Trajectory [";
    str << "size:" << getTrajectoryPtr()->getSize() << " ";
    str << "length:" << getTrajectoryPtr()->getLength() << " ";
    str << "time:" << getTrajectoryPtr()->getDuration() << " ";
    str << "]";

    return str.str();
}

PyObject *TrajectoryPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of TrajectoryPy and the Twin object 
    return new TrajectoryPy(new Trajectory);
}

// constructor method
int TrajectoryPy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    PyObject *pcObj=0;
    if (!PyArg_ParseTuple(args, "|O!", &(PyList_Type), &pcObj))
        return -1;

    if (pcObj) {
        Py::List list(pcObj);
        bool first = true;
        for (Py::List::iterator it = list.begin(); it != list.end(); ++it) {
            if (PyObject_TypeCheck((*it).ptr(), &(Robot::WaypointPy::Type))) {
                Robot::Waypoint &wp = *static_cast<Robot::WaypointPy*>((*it).ptr())->getWaypointPtr();
                getTrajectoryPtr()->addWaypoint(wp);
            }
        }
    }
    getTrajectoryPtr()->generateTrajectory();
    return 0;
}


PyObject* TrajectoryPy::insertWaypoints(PyObject * args)
{

    PyObject* o;
    if (PyArg_ParseTuple(args, "O!", &(Base::PlacementPy::Type), &o)) {
        Base::Placement *plm = static_cast<Base::PlacementPy*>(o)->getPlacementPtr();
        getTrajectoryPtr()->addWaypoint(Robot::Waypoint("Pt",*plm));
        getTrajectoryPtr()->generateTrajectory();

        Py_Return;
    }

    PyErr_Clear();
    if (PyArg_ParseTuple(args, "O!", &(Robot::WaypointPy::Type), &o)) {
        Robot::Waypoint &wp = *static_cast<Robot::WaypointPy*>(o)->getWaypointPtr();
        getTrajectoryPtr()->addWaypoint(wp);
        getTrajectoryPtr()->generateTrajectory();
       
        Py_Return;
    }

    PyErr_Clear();
    if (PyArg_ParseTuple(args, "O!", &(PyList_Type), &o)) {
        Py::List list(o);
        bool first = true;
        for (Py::List::iterator it = list.begin(); it != list.end(); ++it) {
            if (PyObject_TypeCheck((*it).ptr(), &(Robot::WaypointPy::Type))) {
                Robot::Waypoint &wp = *static_cast<Robot::WaypointPy*>((*it).ptr())->getWaypointPtr();
                getTrajectoryPtr()->addWaypoint(wp);
            }
        }
        getTrajectoryPtr()->generateTrajectory();
       
        Py_Return;
    }

    Py_Error(PyExc_Exception, "Wrong parameters - waypoint or placement expected");

}

PyObject* TrajectoryPy::position(PyObject * args)
{
    double pos;
    if (!PyArg_ParseTuple(args, "d", &pos))
        return NULL;

    return (new Base::PlacementPy(new Base::Placement(getTrajectoryPtr()->getPosition(pos))));
}

PyObject* TrajectoryPy::velocity(PyObject * args)
{
    double pos;
    if (!PyArg_ParseTuple(args, "d", &pos))
        return NULL;

     // return velocity as float
    return Py::new_reference_to(Py::Float(getTrajectoryPtr()->getVelocity(pos)));
}



Py::Float TrajectoryPy::getDuration(void) const
{
    return Py::Float(getTrajectoryPtr()->getLength());
}

Py::List TrajectoryPy::getWaypoints(void) const
{
     return Py::List();
}

Py::Float TrajectoryPy::getLength(void) const
{
    return Py::Float(getTrajectoryPtr()->getLength());
}



void TrajectoryPy::setWaypoints(Py::List)
{
 
}

PyObject *TrajectoryPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int TrajectoryPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}

