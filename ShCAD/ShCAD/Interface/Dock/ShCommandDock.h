
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#ifndef _SHCOMMANDDOCK_H
#define _SHCOMMANDDOCK_H

#include <qwidget.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qdockwidget.h>

class ShNotifyEvent;


class ShCommandList : public QTextEdit {

	friend class ShCommandContainer;
	friend class ShCommandDock;
private:
	ShCommandList(QWidget *parent = 0);
	~ShCommandList();
};

class ShCommandEdit : public QLineEdit {
	friend class ShCommandContainer;
	friend class ShCommandDock;

private:
	bool calledKeyPressEventByUpdate;
	QString headTitle;

private:
	ShCommandEdit(QWidget *parent = 0);
	~ShCommandEdit();

	void keyPressEvent(QKeyEvent *event);
};

class ShCommandContainer : public QWidget {
	friend class ShCommandDock;
private:
	ShCommandEdit *edit;
	ShCommandList *list;
	
private:
	ShCommandContainer(QWidget *parent = 0);
	~ShCommandContainer();

protected:
	void resizeEvent(QResizeEvent *event);

};

class ShCommandDock : public QDockWidget {

private:
	ShCommandContainer *container;

public:
	ShCommandDock(QWidget *parent = 0);
	~ShCommandDock();

	void Update(QKeyEvent *event);
	void Notify(ShNotifyEvent *event);

protected:
	void closeEvent(QCloseEvent *event);

};

#endif //_SHCOMMANDWIDGET_H