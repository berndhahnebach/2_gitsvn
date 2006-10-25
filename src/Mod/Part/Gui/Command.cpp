/***************************************************************************
 *   Copyright (c) J�rgen Riegel          (juergen.riegel@web.de) 2002     *
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
# include <qdir.h>
# include <qfileinfo.h>
# include <qlineedit.h>
#endif

#include <Base/Exception.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/FileDialog.h>
#include <Gui/MainWindow.h>
#include <Gui/Selection.h>

#include <BRepPrimAPI_MakeBox.hxx>
#include <TopoDS_Shape.hxx>

#include "../App/PartFeature.h"
#include "DlgPartBoxImp.h"
#include "DlgPartImportStepImp.h"
#include "DlgPartImportIgesImp.h"

using Gui::FileDialog;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// Part_PickCurveNet
//===========================================================================
DEF_STD_CMD(CmdPartPickCurveNet);

CmdPartPickCurveNet::CmdPartPickCurveNet()
  :Command("Part_PickCurveNet")
{
  sAppModule    = "Part";
  sGroup        = QT_TR_NOOP("Part");
  sMenuText     = QT_TR_NOOP("Pick a cruve network");
  sToolTipText  = QT_TR_NOOP("Pick a cruve network");
  sWhatsThis    = sToolTipText;
  sStatusTip    = sToolTipText;
  sPixmap       = "Test1";
  iAccel        = 0;
}

void CmdPartPickCurveNet::activated(int iMsg)
{

}

//===========================================================================
// Std_Test1
//===========================================================================
DEF_STD_CMD(CmdPartTest1);

CmdPartTest1::CmdPartTest1()
  :Command("Part_Test1")
{
  sAppModule  = "Part";
  sGroup      = QT_TR_NOOP("Part");
  sMenuText   = QT_TR_NOOP("Test1");
  sToolTipText= QT_TR_NOOP("Part Test function 1");
  sWhatsThis  = sToolTipText;
  sStatusTip  = sToolTipText;
  sPixmap     = "Test1";
  iAccel      = Qt::CTRL+Qt::Key_T;
}


void CmdPartTest1::activated(int iMsg)
{
  PartGui::DlgPartBoxImp cDlg(Gui::getMainWindow(),"Part Box",true);
  cDlg.exec();
}

//===========================================================================
// Std_Test2
//===========================================================================
DEF_STD_CMD(CmdPartTest2);

CmdPartTest2::CmdPartTest2()
  :Command("Part_Test2")
{
  sAppModule  = "Part";
  sGroup      = QT_TR_NOOP("Part");
  sMenuText   = QT_TR_NOOP("Test2");
  sToolTipText= QT_TR_NOOP("Part Test function 2");
  sWhatsThis  = sToolTipText;
  sStatusTip  = sToolTipText;
  sPixmap     = "Test2";
  iAccel      = 0;
}


void CmdPartTest2::activated(int iMsg)
{
  App::Document *pcDoc = getDocument();
  if(!pcDoc) return;
  updateActive();
}


//===========================================================================
// Part_Box
//===========================================================================
DEF_STD_CMD_A(CmdPartBox);

CmdPartBox::CmdPartBox()
  :Command("Part_Box")
{
  sAppModule    = "Part";
  sGroup        = QT_TR_NOOP("Part");
  sMenuText     = QT_TR_NOOP("Box");
  sToolTipText  = QT_TR_NOOP("Create or change a Box feature");
  sWhatsThis    = sToolTipText;
  sStatusTip    = sToolTipText;
  sPixmap       = "Part_Box";
  iAccel        = 0;
}


void CmdPartBox::activated(int iMsg)
{
  PartGui::DlgPartBoxImp cDlg(Gui::getMainWindow(),"Part Box",true);
  if ( cDlg.exec()== QDialog::Accepted )
  {
    openCommand("Part Box Create");
    doCommand(Doc,"f = App.document().addObject(\"Part::Box\",\"PartBox\")");
    doCommand(Doc,"f.x = %f",cDlg.XLineEdit->text().toFloat());
    doCommand(Doc,"f.y = %f",cDlg.YLineEdit->text().toFloat());
    doCommand(Doc,"f.z = %f",cDlg.ZLineEdit->text().toFloat());
    doCommand(Doc,"f.l = %f",cDlg.ULineEdit->text().toFloat());
    doCommand(Doc,"f.w = %f",cDlg.VLineEdit->text().toFloat());
    doCommand(Doc,"f.h = %f",cDlg.WLineEdit->text().toFloat());
    commitCommand();
  
    updateActive();
  }
}

bool CmdPartBox::isActive(void)
{
  if( getActiveGuiDocument() )
    return true;
  else
    return false;
}

//===========================================================================
// Part_Box2
//===========================================================================
DEF_STD_CMD_A(CmdPartBox2);

CmdPartBox2::CmdPartBox2()
  :Command("Part_Box2")
{
  sAppModule    = "Part";
  sGroup        = QT_TR_NOOP("Part");
  sMenuText     = QT_TR_NOOP("Box fix 1");
  sToolTipText  = QT_TR_NOOP("Create a Box feature without Dialog");
  sWhatsThis    = sToolTipText;
  sStatusTip    = sToolTipText;
  sPixmap       = "Part_Box";
  iAccel        = 0;
}


void CmdPartBox2::activated(int iMsg)
{
  openCommand("PartBox Create");

  doCommand(Doc,"f = App.document().addObject(\"Part::Box\",\"PartBox\")");
  doCommand(Doc,"f.x = 0.0");
  doCommand(Doc,"f.y = 0.0");
  doCommand(Doc,"f.z = 0.0");
  doCommand(Doc,"f.l = 100.0");
  doCommand(Doc,"f.w = 100.0");
  doCommand(Doc,"f.h = 100.0");

  updateActive();

  commitCommand();
}

bool CmdPartBox2::isActive(void)
{
  if( getActiveGuiDocument() )
    return true;
  else
    return false;
}

//===========================================================================
// Part_Box3
//===========================================================================
DEF_STD_CMD_A(CmdPartBox3);

CmdPartBox3::CmdPartBox3()
  :Command("Part_Box3")
{
  sAppModule    = "Part";
  sGroup        = QT_TR_NOOP("Part");
  sMenuText     = QT_TR_NOOP("Box fix 2");
  sToolTipText  = QT_TR_NOOP("Create a box feature without dialog");
  sWhatsThis    = sToolTipText;
  sStatusTip    = sToolTipText;
  sPixmap       = "Part_Box";
  iAccel        = 0;
}


void CmdPartBox3::activated(int iMsg)
{
  openCommand("PartBox Create");

  doCommand(Doc,"f = App.document().addObject(\"Part::Box\",\"PartBox\")");
  doCommand(Doc,"f.x = 50.0");
  doCommand(Doc,"f.y = 50.0");
  doCommand(Doc,"f.z = 50.0");
  doCommand(Doc,"f.l = 100.0");
  doCommand(Doc,"f.w = 100.0");
  doCommand(Doc,"f.h = 100.0");
 
  updateActive();

  commitCommand();
}

bool CmdPartBox3::isActive(void)
{
  if( getActiveGuiDocument() )
    return true;
  else
    return false;
}

//===========================================================================
// Part_Cut
//===========================================================================
DEF_STD_CMD_A(CmdPartCut);

CmdPartCut::CmdPartCut()
  :Command("Part_Cut")
{
  sAppModule    = "Part";
  sGroup        = QT_TR_NOOP("Part");
  sMenuText		  = QT_TR_NOOP("Cut");
  sToolTipText  = QT_TR_NOOP("Create or change a Cut feature");
  sWhatsThis    = sToolTipText;
  sStatusTip    = sToolTipText;
  sPixmap       = "Part_Box";
  iAccel        = 0;
}


void CmdPartCut::activated(int iMsg)
{
  unsigned int n = getSelection().countObjectsOfType(Part::Feature::getClassTypeId());
  if(n != 2)
  {
    Base::Console().Warning("Please, select two shapes (Part Feature)");
    return;
  }

  string FeatName = getUniqueObjectName("Cut");

  vector<Gui::SelectionSingleton::SelObj> Sel = getSelection().getSelection();

  openCommand("Part Cut");
  doCommand(Doc,"App.document().addObject(\"Part::Cut\",\"%s\")",FeatName.c_str());
  doCommand(Doc,"App.document().%s.Base = App.document().%s",FeatName.c_str(),Sel[0].FeatName);
  doCommand(Doc,"App.document().%s.Tool = App.document().%s",FeatName.c_str(),Sel[1].FeatName);
  doCommand(Gui,"Gui.document().hide(\"%s\")",Sel[0].FeatName);
  doCommand(Gui,"Gui.document().hide(\"%s\")",Sel[1].FeatName);
  updateActive();
  commitCommand();
}

bool CmdPartCut::isActive(void)
{
  return getSelection().countObjectsOfType(Part::Feature::getClassTypeId())==2;
}

//===========================================================================
// CmdPartImport
//===========================================================================
DEF_STD_CMD_A(CmdPartImport);

CmdPartImport::CmdPartImport()
  :Command("Part_Import")
{
  sAppModule    = "Part";
  sGroup        = QT_TR_NOOP("Part");
  sMenuText     = QT_TR_NOOP("Import CAD");
  sToolTipText  = QT_TR_NOOP("Imports a CAD file");
  sWhatsThis    = sToolTipText;
  sStatusTip    = sToolTipText;
  sPixmap       = "Part_Box";
  iAccel        = 0;
}


void CmdPartImport::activated(int iMsg)
{
  QString dir = Gui::FileDialog::getWorkingDirectory();
  QString filter = "STEP (*.stp *.step);;IGES (*.igs *.iges);;BREP (*.brp *.brep *.BREP);;All Files (*.*)";
  QString fn = Gui::FileDialog::getOpenFileName( dir, filter, Gui::getMainWindow() );
  if (! fn.isEmpty() )
  {
    App::Document* pDoc = getDocument();
    if ( !pDoc ) return; // no document
    openCommand("Part Import Create");
    doCommand(Doc, "import Part");
    doCommand(Doc, "Part.insert(\"%s\",\"%s\")", fn.latin1(), pDoc->getName());
    commitCommand();

    Gui::FileDialog::setWorkingDirectory(fn);
  }
}

bool CmdPartImport::isActive(void)
{
  if( getActiveGuiDocument() )
    return true;
  else
    return false;
}

//===========================================================================
// PartImportCurveNet
//===========================================================================
DEF_STD_CMD_A(CmdPartImportCurveNet);

CmdPartImportCurveNet::CmdPartImportCurveNet()
  :Command("Part_ImportCurveNet")
{
  sAppModule  = "Part";
  sGroup      = QT_TR_NOOP("Part");
  sMenuText   = QT_TR_NOOP("Import a curve network");
  sToolTipText= QT_TR_NOOP("Import a curve network");
  sWhatsThis  = sToolTipText;
  sStatusTip  = sToolTipText;
  sPixmap     = "Part_Box";
  iAccel      = 0;
}

void CmdPartImportCurveNet::activated(int iMsg)
{
  QString dir = Gui::FileDialog::getWorkingDirectory();
  QString filter = "All CAD (*.stp *. step *.igs *.iges *.brp *.brep );;STEP (*.stp *. step);;IGES (*.igs *.iges);;BREP (*.brp *.brep );;All Files (*.*)";
  QString fn = Gui::FileDialog::getOpenFileName( dir, filter, Gui::getMainWindow() );
  if (! fn.isEmpty() )
  {
    QFileInfo fi; fi.setFile(fn);
    openCommand("Part Import Curve Net");
    doCommand(Doc,"f = App.document().addObject(\"Part::CurveNet\",\"%s\")", fi.baseName().latin1());
    doCommand(Doc,"f.FileName = \"%s\"",fn.ascii());
    commitCommand();
    updateActive();

    Gui::FileDialog::setWorkingDirectory(fn);
  }
}

bool CmdPartImportCurveNet::isActive(void)
{
  if( getActiveGuiDocument() )
    return true;
  else
    return false;
}


void CreatePartCommands(void)
{
  Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();

  rcCmdMgr.addCommand(new CmdPartTest1());
  rcCmdMgr.addCommand(new CmdPartTest2());

  rcCmdMgr.addCommand(new CmdPartCut());
  rcCmdMgr.addCommand(new CmdPartBox());
  rcCmdMgr.addCommand(new CmdPartBox2());
  rcCmdMgr.addCommand(new CmdPartBox3());

  rcCmdMgr.addCommand(new CmdPartImport());
  rcCmdMgr.addCommand(new CmdPartImportCurveNet());
  rcCmdMgr.addCommand(new CmdPartPickCurveNet());
} 

