
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
#include "Interface\Menu\ShMenuBar.h"
#include <qmdiarea.h>
#include <qdockwidget.h>
#include <qtoolbar.h>
#include "Interface\Ribbon\ShRibbonMenu.h"
#include "ShStatusBar.h"
#include "Dock\ShCommandDock.h"
#include "Singleton Pattern\ShChangeManager.h"
#include "Interface\ToolBar\ShPropertyToolBar.h"
#include "Interface\ToolBar\ShLayerToolBar.h"
#include "Interface\ToolBar\ShObjectSnapToolBar.h"

ShCAD::ShCAD(QWidget *parent)
	: QMainWindow(parent){

	
	this->InitWidgets();
	this->NewActionClicked();

	

	
	connect(this->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(SubActivatedWindowChanged(QMdiSubWindow*)));

}

ShCAD::~ShCAD(){
	
	if (this->mdiArea != NULL)
		delete this->mdiArea;

	
}

#include "ShGraphicView.h"
#include "Singleton Pattern\ShWidgetManager.h"
void ShCAD::NewActionClicked() {
	
	if (this->mdiArea->subWindowList().size() == 0) {
		this->ActivateWidgets();
	}
	
	
	ShGraphicView *newWidget = new ShGraphicView(this->mdiArea);
	newWidget->setMinimumSize(400, 400);

	this->mdiArea->addSubWindow(newWidget,Qt::WindowFlags::enum_type::SubWindow);
	newWidget->showMaximized();
	
	ShWidgetManager::GetInstance()->Add(newWidget);
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

void ShCAD::SubActivatedWindowChanged(QMdiSubWindow *window) {

	if (this->mdiArea->subWindowList().size() == 0)
		this->DeActivateWidgets();


}

void ShCAD::InitWidgets() {

	this->menuBar = new ShMenuBar(this);
	this->setMenuBar(this->menuBar);
	

	this->mdiArea = new QMdiArea;
	this->mdiArea->setDocumentMode(true);
	this->mdiArea->hide();

	this->ribbon = new ShRibbonMenu(150, this);
	this->ribbon->setWindowTitle("RibbonBar");
	this->ribbon->hide();
	

	this->statusBar = new ShStatusBar(this);
	this->setStatusBar(this->statusBar);
	this->statusBar->hide();
	

	this->commandDock = new ShCommandDock(this);
	this->commandDock->setWindowTitle("Command");
	this->commandDock->hide();
	
	this->dock = new QDockWidget(this);
	this->dock->installEventFilter(this);
	this->dock->hide();

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Register(this->statusBar);
	manager->Register(this->commandDock);

	this->propertyToolBar = new ShPropertyToolBar(this);
	this->propertyToolBar->setWindowTitle("Property");
	this->propertyToolBar->hide();

	this->layerToolBar = new ShLayerToolBar(this);
	this->layerToolBar->setWindowTitle("Layer");
	this->layerToolBar->hide();

	this->objectSnapToolBar = new ShObjectSnapToolBar(this);
	this->objectSnapToolBar->setWindowTitle("ObjectSnap");
	this->objectSnapToolBar->hide();
	
}

void ShCAD::ActivateWidgets() {

	this->menuBar->ActivateMenu();

	this->setCentralWidget(this->mdiArea);
	this->mdiArea->show();

	this->addToolBar(this->ribbon);
	this->ribbon->show();
	this->addToolBarBreak();

	this->statusBar->show();
	
	this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, this->commandDock);
	this->commandDock->show();

	this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, this->dock);
	this->dock->show();
	
	this->addToolBar(Qt::ToolBarArea::TopToolBarArea,this->propertyToolBar);
	this->propertyToolBar->show();

	this->addToolBar(Qt::ToolBarArea::TopToolBarArea, this->layerToolBar);
	this->layerToolBar->show();

	this->addToolBar(Qt::ToolBarArea::TopToolBarArea, this->objectSnapToolBar);
	this->objectSnapToolBar->show();


}

void ShCAD::DeActivateWidgets() {

	this->menuBar->DeActivateMenu();

	this->takeCentralWidget();
	this->removeToolBar(this->ribbon);
	this->statusBar->hide();
	this->removeDockWidget(this->commandDock);
	this->removeDockWidget(this->dock);
	this->removeToolBar(this->propertyToolBar);
	this->removeToolBar(this->layerToolBar);
	this->removeToolBar(this->objectSnapToolBar);
}