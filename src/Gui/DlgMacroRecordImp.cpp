/***************************************************************************
 *   Copyright (c) 2002 J�rgen Riegel <juergen.riegel@web.de>              *
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

#ifndef __Qt4All__
# include "Qt4All.h"
#endif

#ifndef __Qt3All__
# include "Qt3All.h"
#endif

#include "Macro.h"
#include "Application.h"
#include "MainWindow.h"
#include "DlgMacroRecordImp.h"
#include "FileDialog.h"


using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgMacroRecordImp */

/**
 *  Constructs a DlgMacroRecordImp which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
DlgMacroRecordImp::DlgMacroRecordImp( QWidget* parent, Qt::WFlags fl )
    : QDialog( parent, fl ), WindowParameter("Macro")
{
  this->setupUi(this);
  // get the macro home path
  _cMacroPath = getWindowParameter()->GetASCII("MacroPath",App::GetApplication().GetHomePath());
  // check on PATHSEP at the end
  std::string::iterator It = _cMacroPath.end();
  It--;
  if(*It != PATHSEP)
    _cMacroPath += PATHSEP;

  // get a pointer to the macro manager
  _pcMacroMngr = Application::Instance->macroManager();

  // check if a macro recording is in progress
  _pcMacroMngr->isOpen() ? buttonStart->setEnabled(false) : buttonStop->setEnabled(false);
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgMacroRecordImp::~DlgMacroRecordImp()
{
  // no need to delete child widgets, Qt does it all for us
}

/**
 * Starts the record of the macro.
 */
void DlgMacroRecordImp::on_buttonStart_clicked()
{
  // test if the path already set
  if(lineEditPath->text().isEmpty())
  {
    QMessageBox::information( getMainWindow(), tr("FreeCAD - Macro recorder"),
                                         tr("Specify first a place to save."));
    return;
  }

  // search in the macro path first for an already existing macro
  QString fn = (_cMacroPath + lineEditPath->text().toStdString()).c_str();
  if ( !fn.endsWith(".FCMacro") ) fn += ".FCMacro";
  QFileInfo fi(fn);
  if ( fi.isFile() && fi.exists() )
  {
    if ( QMessageBox::question( this, tr("Existing macro"), tr("The macro '%1' already exists. Do you want to overwrite?").arg(fn),
                                QMessageBox::Yes, QMessageBox::No|QMessageBox::Default|QMessageBox::Escape ) == QMessageBox::No )
    return;
  }

  // open the macro recording
  _pcMacroMngr->open(MacroManager::File,(_cMacroPath + lineEditPath->text().toStdString()).c_str());
  accept();
}

/**
 * Abort the macro.
 */
void DlgMacroRecordImp::on_buttonCancel_clicked()
{
  if(_pcMacroMngr->isOpen())
  {
    _pcMacroMngr->cancel();
  }
  
  QDialog::reject();
}

/**
 * Stops the record of the macro.and save to the file.
 */
void DlgMacroRecordImp::on_buttonStop_clicked()
{
  if(_pcMacroMngr->isOpen())
  {
    // ends the macrorecording and save the file...
    _pcMacroMngr->commit();
  }

  QDialog::accept();
}

#include "moc_DlgMacroRecordImp.cpp"

