/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *   for detail see the LICENCE text file.                                 *
 *   J�rgen Riegel 2002                                                    *
 *                                                                         *
 ***************************************************************************/

#include "PreCompiled.h"
#ifndef _PreComp_
# include <QMessageBox>
#endif

#include <vector>

#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/Selection.h>
#include <Gui/MainWindow.h>
#include <Gui/FileDialog.h>

#include <Mod/Part/App/PartFeature.h>
#include <Mod/Drawing/App/FeaturePage.h>


#include "DrawingView.h"

using namespace DrawingGui;
using namespace std;


//===========================================================================
// CmdDrawingOpen
//===========================================================================

DEF_STD_CMD(CmdDrawingOpen);

CmdDrawingOpen::CmdDrawingOpen()
	:Command("Drawing_Open")
{
    sAppModule      = "Drawing";
    sGroup          = QT_TR_NOOP("Drawing");
    sMenuText       = QT_TR_NOOP("Open SVG...");
    sToolTipText    = QT_TR_NOOP("Open a scalable vector graphic");
    sWhatsThis      = "Drawing_Open";
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/document-new";
}


void CmdDrawingOpen::activated(int iMsg)
{
    // Reading an image
    QString filename = Gui::FileDialog::getOpenFileName(Gui::getMainWindow(), QObject::tr("Choose an SVG file to open"), QString::null, 
                                           QObject::tr("Scalable Vector Graphics (*.svg *.svgz)"));
    if (!filename.isEmpty())
    {
        // load the file with the module
        Command::doCommand(Command::Gui, "import Drawing, DrawingGui");
        Command::doCommand(Command::Gui, "DrawingGui.open(\"%s\")", (const char*)filename.toUtf8());
    }
}

//===========================================================================
// Drawing_NewA3Landscape
//===========================================================================

DEF_STD_CMD_A(CmdDrawingNewA3Landscape);

CmdDrawingNewA3Landscape::CmdDrawingNewA3Landscape()
	:Command("Drawing_NewA3Landscape")
{
    sAppModule      = "Drawing";
    sGroup          = QT_TR_NOOP("Drawing");
    sMenuText       = QT_TR_NOOP("Insert new A3 landscape drawing");
    sToolTipText    = QT_TR_NOOP("Insert new A3 landscape drawing");
    sWhatsThis      = "Drawing_NewA3Landscape";
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/drawing-landscape-A3";
}


void CmdDrawingNewA3Landscape::activated(int iMsg)
{
  // Note: On Linux it is bad behaviour to mix up data files with binary files in the same directory.
# ifdef TEMPLATEDIR
  std::string Path = TEMPLATEDIR; Path += "/A3_Landscape.svg";
# else
  std::string Path(App::Application::Config()["AppHomePath"] + "Mod/Drawing/Templates/A3_Landscape.svg");
#endif
  std::string FeatName = getUniqueObjectName("Page");
  
  doCommand(Doc,"App.activeDocument().addObject('Drawing::FeaturePage','%s')",FeatName.c_str());
  //doCommand(Doc,"App.activeDocument().%s.Template = App.ConfigGet('AppHomePath')+'Mod/Drawing/Templates/A4_Simple.svg'",FeatName.c_str());
  doCommand(Doc,"App.activeDocument().%s.Template = '%s'",FeatName.c_str(), Path.c_str());    
}

bool CmdDrawingNewA3Landscape::isActive(void)
{
  if( getActiveGuiDocument() )
    return true;
  else
    return false;
}


//===========================================================================
// Drawing_NewView
//===========================================================================

DEF_STD_CMD(CmdDrawingNewView);

CmdDrawingNewView::CmdDrawingNewView()
	:Command("Drawing_NewView")
{
    sAppModule      = "Drawing";
    sGroup          = QT_TR_NOOP("Drawing");
    sMenuText       = QT_TR_NOOP("Insert a new View of a Part in the active drawing");
    sToolTipText    = QT_TR_NOOP("Insert a new View of a Part in the active drawing");
    sWhatsThis      = "Drawing_NewView";
    sStatusTip      = sToolTipText;
    sPixmap         = "actions/drawing-view";
}


void CmdDrawingNewView::activated(int iMsg)
{

   unsigned int n = getSelection().countObjectsOfType(Part::Feature::getClassTypeId());
    if (n != 1) {
        QMessageBox::warning(Gui::getMainWindow(), QObject::tr("Wrong selection"),
            QObject::tr("Select a Part object."));
        return;
    }

	App::DocumentObject *page = this->getDocument()->getObject("Page");
	if ( !page /*|| !page->getClassTypeId().isDerivedFrom(Drawing::FeaturePage::getClassTypeId()) */){
        QMessageBox::warning(Gui::getMainWindow(), QObject::tr("No page to insert"),
            QObject::tr("Create a page to insert."));
        return;
    }

    std::string FeatName = getUniqueObjectName("View");

    std::vector<Gui::SelectionSingleton::SelObj> Sel = getSelection().getSelection();

    openCommand("Create view");
    doCommand(Doc,"App.activeDocument().addObject('Drawing::FeatureViewPart','%s')",FeatName.c_str());
    doCommand(Doc,"App.activeDocument().%s.Source = App.activeDocument().%s",FeatName.c_str(),Sel[0].FeatName);
    doCommand(Doc,"App.activeDocument().%s.Direction = (0.0,0.0,1.0)",FeatName.c_str());
    doCommand(Doc,"App.activeDocument().%s.X = 10.0",FeatName.c_str());
    doCommand(Doc,"App.activeDocument().%s.Y = 10.0",FeatName.c_str());
    doCommand(Doc,"App.activeDocument().%s.Scale = 1.0",FeatName.c_str());
    doCommand(Doc,"App.activeDocument().Page.addObject(App.activeDocument().%s)",FeatName.c_str());
    updateActive();
    commitCommand();

}

//===========================================================================
// Drawing_ExportPage
//===========================================================================

DEF_STD_CMD_A(CmdDrawingExportPage);

CmdDrawingExportPage::CmdDrawingExportPage()
  : Command("Drawing_ExportPage")
{
    // seting the
    sGroup        = QT_TR_NOOP("File");
    sMenuText     = QT_TR_NOOP("&Export page...");
    sToolTipText  = QT_TR_NOOP("Export a page to a SVG file");
    sWhatsThis    = "Drawing_ExportPage";
    sStatusTip    = QT_TR_NOOP("Export a page to a SVG file");
    sPixmap       = "Save";
    iAccel        = 0;
}

void CmdDrawingExportPage::activated(int iMsg)
{
	unsigned int n = getSelection().countObjectsOfType(Drawing::FeaturePage::getClassTypeId());
    if (n != 1) {
        QMessageBox::warning(Gui::getMainWindow(), QObject::tr("Wrong selection"),
            QObject::tr("Select one Page object."));
        return;
    }

    QStringList filter;
    filter << QObject::tr("SVG(*.svg)");
    filter << QObject::tr("All Files (*.*)");

    QString fn = Gui::FileDialog::getSaveFileName(Gui::getMainWindow(), QObject::tr("Export page"), QString(), filter.join(QLatin1String(";;")));
    if (!fn.isEmpty()) {
  	   std::vector<Gui::SelectionSingleton::SelObj> Sel = getSelection().getSelection();
        openCommand("Drawing export page");
		doCommand(Doc,"file = open(App.activeDocument().%s.PageResult,'r')",Sel[0].FeatName);

        commitCommand();
    }
}

bool CmdDrawingExportPage::isActive(void)
{
    return (getActiveGuiDocument() ? true : false);
}



void CreateDrawingCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();

    rcCmdMgr.addCommand(new CmdDrawingOpen());
    rcCmdMgr.addCommand(new CmdDrawingNewA3Landscape());
    rcCmdMgr.addCommand(new CmdDrawingNewView());
    rcCmdMgr.addCommand(new CmdDrawingExportPage());
}
