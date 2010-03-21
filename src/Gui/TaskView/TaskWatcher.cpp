/***************************************************************************
 *   Copyright (c) 2009 J�rgen Riegel <juergen.riegel@web.de>              *
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
#  include <QPixmap>
#endif


#include <QObject>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/BitmapFactory.h>
#include <Gui/TaskView/TaskView.h>
#include <Gui/Action.h>

#include "TaskWatcher.h"


using namespace Gui::TaskView;


//**************************************************************************
//**************************************************************************
// TaskWatcher
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskWatcher::TaskWatcher( const char* Filter )
    : QObject(0),SelectionFilter(Filter)
{
    
}

TaskWatcher::~TaskWatcher()
{
    for(std::vector<QWidget*>::iterator it=Content.begin();it!=Content.end();++it){
        delete(*it);
        *it = 0;
    }

}

//==== implementer ===========================================================================

std::vector<QWidget*> &TaskWatcher::getWatcherContent(void)
{
    return Content;
}

//==== calls from the TaskView ===============================================================

bool TaskWatcher::shouldShow()
{
    return false;
}

//**************************************************************************
//**************************************************************************
// TaskWatcherCommands
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskWatcherCommands::TaskWatcherCommands(const char* Filter,const char* commands[], const char* name, const char* pixmap )
    :TaskWatcher(Filter)
{
    CommandManager &mgr = Gui::Application::Instance->commandManager();
    Gui::TaskView::TaskBox *tb = new Gui::TaskView::TaskBox(BitmapFactory().pixmap(pixmap), QString::fromUtf8(name), true, 0);


    for(const char** i=commands;*i;i++){
        if(!i) break;
        Command *c = mgr.getCommandByName(*i);
        if(c){
           	iisIconLabel *label = new iisIconLabel(BitmapFactory().pixmap(c->getPixmap()), QString::fromUtf8(c->getMenuText()), tb);
	        tb->addIconLabel(label);
            Gui::Action *a = c->getAction();
            QObject::connect(label,SIGNAL(clicked()),a,SLOT(onActivated()));
        }

    }

    Content.push_back(tb);
}

TaskWatcherCommands::~TaskWatcherCommands()
{
}

//==== implementer ===========================================================================


//==== calls from the TaskView ===============================================================

bool TaskWatcherCommands::shouldShow()
{
    return match();   
}
//**************************************************************************
//**************************************************************************
// TaskWatcherCommandsEmptyDoc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskWatcherCommandsEmptyDoc::TaskWatcherCommandsEmptyDoc(const char* commands[], const char* name, const char* pixmap )
    :TaskWatcherCommands("",commands,name,pixmap)
{
}

TaskWatcherCommandsEmptyDoc::~TaskWatcherCommandsEmptyDoc()
{
}

//==== implementer ===========================================================================


//==== calls from the TaskView ===============================================================

bool TaskWatcherCommandsEmptyDoc::shouldShow()
{
    return App::GetApplication().getActiveDocument() && App::GetApplication().getActiveDocument()->countObjects() == 0;
}


#include "moc_TaskWatcher.cpp"