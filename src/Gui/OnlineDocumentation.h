/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <werner.wm.mayer@gmx.de>              *
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


#ifndef GUI_ONLINEDOCUMENTATION_H
#define GUI_ONLINEDOCUMENTATION_H

#ifndef __Qt4All__
# include "Qt4All.h"
#endif

#include "Command.h"


namespace Gui {

/**
 * Returns the content of an HTML page which gets sent to 
 * the client to be displayed.
 * @author Werner Mayer
 */
  class OnlineDocumentation : public QObject
{
  Q_OBJECT

public:
  OnlineDocumentation();
  ~OnlineDocumentation();

  QByteArray loadResource(const QString& filename) const;

private:
  QStringList files;
};

/** 
 * The HttpServer class implements a simple HTTP server.
 */
class HttpServer : public QTcpServer
{
    Q_OBJECT

public:
  HttpServer(QObject* parent = 0);

  void incomingConnection(int socket);
  void pause();
  void resume();

private slots:
  void readClient();
  void discardClient();

private:
  OnlineDocumentation help;
  bool disabled;
};

// --------------------------------------------------------------------

class StdCmdOnlineHelp : public Command
{
public:
  StdCmdOnlineHelp();
  ~StdCmdOnlineHelp();

protected:
  void activated(int iMsg);

private:
  HttpServer* server;
};

}

#endif // GUI_ONLINEDOCUMENTATION_H
