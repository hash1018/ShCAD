
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

#include "shcad.h"
#include "ShMenuBar.h"
#include <qmdiarea.h>
#include <qdockwidget.h>
#include <qtoolbar.h>
#include "ShRibbonMenu.h"
ShCAD::ShCAD(QWidget *parent)
	: QMainWindow(parent){

	
	this->menuBar = new ShMenuBar(this);
	this->setMenuBar(this->menuBar);
	
	this->mdiArea = new QMdiArea;
	this->setCentralWidget(this->mdiArea);
	this->mdiArea->setDocumentMode(true);
	connect(this->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), SLOT(SubWindowActivated(QMdiSubWindow*)));

	this->dock = new QDockWidget(this);
	this->dock->installEventFilter(this);
	this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, this->dock);
	

	ShRibbonMenu *ribbon = new ShRibbonMenu(150, this);
	ribbon->setWindowTitle("RibbonBar");
	this->addToolBar(ribbon);

	
	QToolBar *temp2 = new QToolBar(this);
	this->addToolBarBreak();
	this->addToolBar(temp2);
}

ShCAD::~ShCAD(){
	

	
}

#include "ShGraphicView2D.h"
#include "ShCADWidget.h"
#include "Singleton Pattern\ShWidgetManager.h"
void ShCAD::NewActionClicked() {
	
	
	
	ShCADWidget *newWidget = new ShCADWidget(new ShGraphicView2D);
	newWidget->setMinimumSize(400, 400);

	this->mdiArea->addSubWindow(newWidget,Qt::WindowFlags::enum_type::SubWindow);
	newWidget->show();
	
	ShWidgetManager::GetInstance()->SetActivatedWidget(newWidget);
	
}





#include <QEvent>
#include <QResizeEvent>
bool ShCAD::eventFilter(QObject *obj, QEvent *event) {
	
	if (event->type() == QEvent::Resize && obj == this->dock) {
		QResizeEvent *resizeEvent = static_cast<QResizeEvent*>(event);
		qDebug("Dock Resized (New Size) - Width: %d Height: %d",
			resizeEvent->size().width(),
			resizeEvent->size().height());
		
		
		this->resizeDocks({ this->dock }, { resizeEvent->size().width() }, 
			Qt::Orientation::Horizontal);

		this->resizeDocks({ this->dock }, { resizeEvent->size().height() }, Qt::Orientation::Vertical);
	}
	
	return QWidget::eventFilter(obj, event);
}

/*
void ShCAD::ShowContextMenu(const QPoint &pos) {

	QMenu contextMenu(tr("Context menu"), this);

	QAction action1("Remove Data Point", this);
	connect(&action1, SIGNAL(triggered()), this, SLOT(TestCustomContextMenu()));
	contextMenu.addAction(&action1);

	contextMenu.exec(mapToGlobal(pos));

}

#include <qmessagebox.h>
void ShCAD::TestCustomContextMenu() {
	QMessageBox box;
	box.exec();

}
*/


void ShCAD::SubWindowActivated(QMdiSubWindow *window) {
	qDebug("SubWindowActivated");

	if (window == 0) {
		qDebug("no more subwindows");
		return;
	}


	ShWidgetManager::GetInstance()->SetActivatedWidget((ShCADWidget*)window);

	//sooner or later  i can add signal here
}