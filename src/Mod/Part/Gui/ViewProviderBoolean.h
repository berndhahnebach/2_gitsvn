/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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


#ifndef PARTGUI_ViewProviderBoolean_H
#define PARTGUI_ViewProviderBoolean_H

#include "ViewProvider.h"


namespace PartGui {

class AppPartGuiExport ViewProviderBoolean : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderBoolean);

public:
    /// constructor
    ViewProviderBoolean();
    /// destructor
    virtual ~ViewProviderBoolean();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
};

/// ViewProvider for the MultiFuse feature
class AppPartGuiExport ViewProviderMultiFuse : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderMultiFuse);

public:
    /// constructor
    ViewProviderMultiFuse();
    /// destructor
    virtual ~ViewProviderMultiFuse();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
};

/// ViewProvider for the MultiFuse feature
class AppPartGuiExport ViewProviderMultiCommon : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderMultiCommon);

public:
    /// constructor
    ViewProviderMultiCommon();
    /// destructor
    virtual ~ViewProviderMultiCommon();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
};


} // namespace PartGui


#endif // PARTGUI_ViewProviderBoolean_H