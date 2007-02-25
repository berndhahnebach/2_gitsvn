/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <werner.wm.mayer@gmx.de>              *
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


#ifndef GUI_WIDGETS_H
#define GUI_WIDGETS_H

#ifndef __Qt4All__
# include "Qt4All.h"
#endif

#ifndef __Qt3All__
# include "Qt3All.h"
#endif

namespace Gui {
class PrefCheckBox;
class CommandViewItemPrivate;

/**
 * The CheckMessageBox class provides an additional QCheckBox to check if
 * the message should appear in future or not.
 * \author Werner Mayer
 */
class GuiExport CheckMessageBox : public QMessageBox
{
  Q_OBJECT

public:
  CheckMessageBox(QWidget * parent=0, const char * name=0);
  ~CheckMessageBox();

  static int information ( QWidget * parent, const QString & caption, const QString & text,
                           int button0, int button1=0, int button2=0);
  static int information ( QWidget * parent, const QString & caption, const QString & text,
                           const QString & button0Text = QString::null, const QString & button1Text = QString::null,
                           const QString & button2Text = QString::null, int defaultButtonNumber = 0, int escapeButtonNumber = -1);
  static int question    ( QWidget * parent, const QString & caption, const QString & text,
                           int button0, int button1=0, int button2=0);
  static int question    ( QWidget * parent, const QString & caption, const QString & text,
                           const QString & button0Text = QString::null, const QString & button1Text = QString::null,
                           const QString & button2Text = QString::null, int defaultButtonNumber = 0, int escapeButtonNumber = -1);
  static int warning     ( QWidget * parent, const QString & caption, const QString & text,
                           int button0, int button1, int button2=0 );
  static int warning     ( QWidget * parent, const QString & caption, const QString & text,
                           const QString & button0Text = QString::null, const QString & button1Text = QString::null,
                           const QString & button2Text = QString::null, int defaultButtonNumber = 0, int escapeButtonNumber = -1 );
  static int critical    ( QWidget * parent, const QString & caption, const QString & text,
                           int button0, int button1, int button2=0 );
  static int critical    ( QWidget * parent, const QString & caption, const QString & text,
                           const QString & button0Text = QString::null, const QString & button1Text = QString::null,
                           const QString & button2Text = QString::null, int defaultButtonNumber = 0, int escapeButtonNumber = -1 );

protected:

  // protected constructor
  CheckMessageBox(const QString & caption, const QString & text, Icon icon, int button0, int button1,
               int button2, QWidget * parent=0, const char * name=0, bool modal=TRUE, Qt::WFlags f=Qt::WStyle_DialogBorder);

private:
  static int _msg( Icon icon, QWidget * parent, const QString & caption, const QString & text,
                   const QString & button0Text = QString::null, const QString & button1Text = QString::null,
                   const QString & button2Text = QString::null, int defaultButtonNumber = 0, int escapeButtonNumber = -1);

  Gui::PrefCheckBox* checkBox;
  Q3GridLayout* layout;
};

// ------------------------------------------------------------------------------

/**
 * This class allows to drag one or more items which
 * correspond to a Command object. The dragged items you
 * can drop onto a @ref Gui::CustomToolBar object
 * @see CommandViewItem, Command
 * \author Werner Mayer
 */
class CommandIconView : public QListWidget
{
  Q_OBJECT

public:
  CommandIconView ( QWidget * parent = 0 );
  virtual ~CommandIconView ();

protected:
  void startDrag ( Qt::DropActions supportedActions );

protected Q_SLOTS:
  void onSelectionChanged( QListWidgetItem * item, QListWidgetItem * );

Q_SIGNALS:
  /** Emits this signal if selection has changed. */
  void emitSelectionChanged( const QString& );
};

// ------------------------------------------------------------------------------

/**
 * The AccelLineEdit class provides a lineedit to specfify shortcuts.
 * \author Werner Mayer
 */
class GuiExport AccelLineEdit : public QLineEdit
{
  Q_OBJECT

public:
  AccelLineEdit ( QWidget * parent=0 );

protected:
  void keyPressEvent ( QKeyEvent * e);
};

// ------------------------------------------------------------------------------

typedef QPair<QString, bool> CheckListItem;

/**
 * The CheckListDialog class provides a dialog with a QListView with
 * checkable items inside.
 * \author Werner Mayer
 */
class GuiExport CheckListDialog : public QDialog
{

  Q_OBJECT

public:
  CheckListDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
  ~CheckListDialog();

  void setCheckableItems( const QStringList& items );
  void setCheckableItems( const Q3ValueList<CheckListItem>& items );
  QStringList getCheckedItems() const;

  void accept ();

private:
  QStringList checked;

  QPushButton* buttonOk;
  QPushButton* buttonCancel;
  Q3GroupBox* GroupBox1;
  Q3ListView* ListView;
  Q3GridLayout* CheckListDialogLayout;
  Q3HBoxLayout* Layout2;
  Q3GridLayout* GroupBox1Layout;
};

// ------------------------------------------------------------------------------

/**
 *  Implementation of a color button.
 * \author Werner Mayer
 */
class GuiExport ColorButton : public QPushButton
{
  Q_OBJECT

  Q_PROPERTY( QColor color READ color WRITE setColor )

public:
  ColorButton( QWidget* parent = 0 );
  ~ColorButton();

  void setColor( const QColor& );
  QColor color() const;

public Q_SLOTS:
  virtual void onChooseColor();

Q_SIGNALS:
  /** Emits this signal when color has changed */
  void changed();

protected:
  void paintEvent ( QPaintEvent* );

private:
  QColor _col;
};

// ------------------------------------------------------------------------------

/**
 * A text label where a url can specified. When the user clicks on the text label the system browser
 * gets opened with the specified url. 
 *
 * This can be used for e.g. in the about dialog where the url of the maintainer of an application
 * can be specified.
 * @author Werner Mayer
 */
class GuiExport UrlLabel : public QLabel
{
  Q_OBJECT
  Q_PROPERTY( QString  url    READ url   WRITE setUrl)

public:
  UrlLabel ( QWidget * parent = 0, Qt::WFlags f = 0 );
  virtual ~UrlLabel();

  QString url() const;

public Q_SLOTS:
  void setUrl( const QString &u );

protected:
  void enterEvent ( QEvent * );
  void leaveEvent ( QEvent * );
  void mouseReleaseEvent ( QMouseEvent * );

private:
  QString _url;
};

} // namespace Gui

#endif // GUI_WIDGETS_H
