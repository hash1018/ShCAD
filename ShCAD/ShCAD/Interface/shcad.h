
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




#ifndef SHCAD_H
#define SHCAD_H

#include <QtWidgets/QMainWindow>

class QMdiArea;
class ShMenuBar;
class ShStatusBar;
class ShRibbonMenu;
class ShCommandDock;
class ShPropertyToolBar;

class QDockWidget;
class QToolBar;
class QMdiSubWindow;
class ShCAD : public QMainWindow{
	Q_OBJECT

private:
	ShMenuBar *menuBar;
	QMdiArea *mdiArea;
	ShStatusBar *statusBar;
	ShRibbonMenu *ribbon;
	ShCommandDock *commandDock;
	ShPropertyToolBar *propertyToolBar;


	QDockWidget *dock;

	QToolBar *toolBar;

public:
	ShCAD(QWidget *parent = 0);
	~ShCAD();

	void NewActionClicked();
	void InitWidgets();

	void ActivateWidgets();
	void DeActivateWidgets();


	private slots:
	void SubActivatedWindowChanged(QMdiSubWindow*);



protected:
	bool eventFilter(QObject *obj, QEvent *event);

	
	//void ShowContextMenu(const QPoint &pos);
	//void TestCustomContextMenu();

	
};

#endif // SHCAD_H
