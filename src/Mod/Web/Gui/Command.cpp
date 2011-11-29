/***************************************************************************
 *   Copyright (c) 2008 J�rgen Riegel (juergen.riegel@web.de)              *
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
#endif

#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/MainWindow.h>
#include <Gui/FileDialog.h>

#include "BrowserView.h"

using namespace std;
using namespace Gui;
using namespace WebGui;


//===========================================================================
// CmdWebOpenWebsite
//===========================================================================

DEF_STD_CMD(CmdWebOpenWebsite);

CmdWebOpenWebsite::CmdWebOpenWebsite()
  : Command("Web_OpenWebsite")
{
    sAppModule      = "Web";
    sGroup          = QT_TR_NOOP("Web");
    sMenuText       = QT_TR_NOOP("Open website...");
    sToolTipText    = QT_TR_NOOP("Opens a website in FreeCAD");
    sWhatsThis      = sToolTipText;
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/web-browser";
}


void CmdWebOpenWebsite::activated(int iMsg)
{
    doCommand(Doc,"import WebGui");
    doCommand(Command::Gui,"WebGui.openBrowser('http://free-cad.sf.net/')");
}

//===========================================================================
// CmdWebBrowserBack
//===========================================================================

DEF_STD_CMD_A(CmdWebBrowserBack);

CmdWebBrowserBack::CmdWebBrowserBack()
  : Command("Web_BrowserBack")
{
    sAppModule      = "Web";
    sGroup          = QT_TR_NOOP("Web");
    sMenuText       = QT_TR_NOOP("Previous page");
    sToolTipText    = QT_TR_NOOP("Go back to the previous page");
    sWhatsThis      = sToolTipText;
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/web-previous";
}

void CmdWebBrowserBack::activated(int iMsg)
{
    doCommand(Command::Gui,"Gui.SendMsgToActiveView('Back')");
}

bool CmdWebBrowserBack::isActive(void)
{
    return getGuiApplication()->sendHasMsgToActiveView("Back");
}

//===========================================================================
// CmdWebBrowserNext
//===========================================================================

DEF_STD_CMD_A(CmdWebBrowserNext);

CmdWebBrowserNext::CmdWebBrowserNext()
  : Command("Web_BrowserNext")
{
    sAppModule      = "Web";
    sGroup          = QT_TR_NOOP("Web");
    sMenuText       = QT_TR_NOOP("Next page");
    sToolTipText    = QT_TR_NOOP("Go to the next page");
    sWhatsThis      = sToolTipText;
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/web-next";
}

void CmdWebBrowserNext::activated(int iMsg)
{
    doCommand(Command::Gui,"Gui.SendMsgToActiveView('Next')");
}

bool CmdWebBrowserNext::isActive(void)
{
    return getGuiApplication()->sendHasMsgToActiveView("Next");
}

//===========================================================================
// CmdWebBrowserRefresh
//===========================================================================

DEF_STD_CMD_A(CmdWebBrowserRefresh);

CmdWebBrowserRefresh::CmdWebBrowserRefresh()
  : Command("Web_BrowserRefresh")
{
    sAppModule      = "Web";
    sGroup          = QT_TR_NOOP("Web");
    sMenuText       = QT_TR_NOOP("Refresh web page");
    sToolTipText    = QT_TR_NOOP("Refresh web page");
    sWhatsThis      = sToolTipText;
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/web-refresh";
}

void CmdWebBrowserRefresh::activated(int iMsg)
{
    doCommand(Command::Gui,"Gui.SendMsgToActiveView('Refresh')");
}

bool CmdWebBrowserRefresh::isActive(void)
{
    return getGuiApplication()->sendHasMsgToActiveView("Refresh");
}
//===========================================================================
// CmdWebBrowserStop
//===========================================================================

DEF_STD_CMD_A(CmdWebBrowserStop);

CmdWebBrowserStop::CmdWebBrowserStop()
	:Command("Web_BrowserStop")
{
    sAppModule      = "Web";
    sGroup          = QT_TR_NOOP("Web");
    sMenuText       = QT_TR_NOOP("Stop loading");
    sToolTipText    = QT_TR_NOOP("Stop the current loading");
    sWhatsThis      = sToolTipText;
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/web-stop";
}


void CmdWebBrowserStop::activated(int iMsg)
{
    doCommand(Command::Gui,"Gui.SendMsgToActiveView('Stop')");
}

bool CmdWebBrowserStop::isActive(void)
{
    return getGuiApplication()->sendHasMsgToActiveView("Stop");
}

//===========================================================================
// CmdWebBrowserZoomIn
//===========================================================================

DEF_STD_CMD_A(CmdWebBrowserZoomIn);

CmdWebBrowserZoomIn::CmdWebBrowserZoomIn()
  : Command("Web_BrowserZoomIn")
{
    sAppModule      = "Web";
    sGroup          = QT_TR_NOOP("Web");
    sMenuText       = QT_TR_NOOP("Zoom in");
    sToolTipText    = QT_TR_NOOP("Zoom into the page");
    sWhatsThis      = sToolTipText;
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/web-zoom-in";
}

void CmdWebBrowserZoomIn::activated(int iMsg)
{
    doCommand(Command::Gui,"Gui.SendMsgToActiveView('ZoomIn')");
}

bool CmdWebBrowserZoomIn::isActive(void)
{
    return getGuiApplication()->sendHasMsgToActiveView("ZoomIn");
}

//===========================================================================
// CmdWebBrowserZoomOut
//===========================================================================

DEF_STD_CMD_A(CmdWebBrowserZoomOut);

CmdWebBrowserZoomOut::CmdWebBrowserZoomOut()
  : Command("Web_BrowserZoomOut")
{
    sAppModule      = "Web";
    sGroup          = QT_TR_NOOP("Web");
    sMenuText       = QT_TR_NOOP("Zoom out");
    sToolTipText    = QT_TR_NOOP("Zoom out of the page");
    sWhatsThis      = sToolTipText;
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/web-zoom-out";
}

void CmdWebBrowserZoomOut::activated(int iMsg)
{
    doCommand(Command::Gui,"Gui.SendMsgToActiveView('ZoomOut')");
}

bool CmdWebBrowserZoomOut::isActive(void)
{
    return getGuiApplication()->sendHasMsgToActiveView("ZoomOut");
}


void CreateWebCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();

    rcCmdMgr.addCommand(new CmdWebOpenWebsite());
    rcCmdMgr.addCommand(new CmdWebBrowserBack());
    rcCmdMgr.addCommand(new CmdWebBrowserNext());
    rcCmdMgr.addCommand(new CmdWebBrowserRefresh());
    rcCmdMgr.addCommand(new CmdWebBrowserStop());
    rcCmdMgr.addCommand(new CmdWebBrowserZoomIn());
    rcCmdMgr.addCommand(new CmdWebBrowserZoomOut());
 }
