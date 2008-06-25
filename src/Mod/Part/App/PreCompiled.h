#ifndef __PRECOMPILED__
#define __PRECOMPILED__

#include <FCConfig.h>


// Exporting of App classes
#ifdef FC_OS_WIN32
# define AppPartExport __declspec(dllexport)
# define PartExport    __declspec(dllexport)
#else // for Linux
# define AppPartExport
# define PartExport
#endif


#ifdef _PreComp_

/// here get the warnings of to long specifieres disabled (needed for VC6)
#ifdef _MSC_VER
#	pragma warning( disable : 4251 )
#	pragma warning( disable : 4275 )
#	pragma warning( disable : 4503 )
#	pragma warning( disable : 4786 )  // specifier longer then 255 chars
#endif

// standard
#include <list>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <assert.h>

#include <vector>
#include <list>
#include <set>
#include <map>

// Xerces
#include <xercesc/util/XercesDefs.hpp>

// Boost
#include <boost/signals.hpp>
#include <boost/bind.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/utility.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>

#include "OpenCascadeAll.h"

#endif //_PreComp_

#ifndef _Standard_Version_HeaderFile
#include <Standard_Version.hxx>
#endif

#if defined(OCC_VERSION_MAJOR) && defined(OCC_VERSION_MINOR) && defined(OCC_VERSION_MAINTENANCE)
#   define OCC_HEX_VERSION ((OCC_VERSION_MAJOR<<16)+(OCC_VERSION_MINOR<<8)+(OCC_VERSION_MAINTENANCE))
#else
#   define OCC_HEX_VERSION 0x050000 // use an old version
#endif


#endif
