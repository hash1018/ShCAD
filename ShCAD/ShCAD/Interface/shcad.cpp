
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
#include "Interface\Ribbon\ShRibbonMenu.h"
#include "ShStatusBar.h"
#include "Dock\ShCommandDock.h"
#include "Singleton Pattern\ShChangeManager.h"
#include "Interface\ToolBar\ShToolBarContainer.h"


ShCAD::ShCAD(QWidget *parent)
	: QMainWindow(parent){

	this->InitWidgets();
	this->NewActionClicked();

	this->contextMenu = new QMenu("ContextMenu", this);
	this->contextMenu->addMenu(this->toolBarContainer->GetToolBarMenu());
	//this->contextMenu->addAction("sdad", this, SLOT(TestCustomContextMenu()));


	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowContextMenu(const QPoint &)));

	
	connect(this->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(SubActivatedWindowChanged(QMdiSubWindow*)));

}

ShCAD::~ShCAD(){
	
	if (this->mdiArea != NULL)
		delete this->mdiArea;

	if (this->toolBarContainer != NULL)
		delete this->toolBarContainer;
	
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
	
	if (event->type() == QEvent::Resize && obj == this->commandDock) {
		QResizeEvent *resizeEvent = static_cast<QResizeEvent*>(event);
		qDebug("Dock Resized (New Size) - Width: %d Height: %d",
			resizeEvent->size().width(),
			resizeEvent->size().height());
	
		this->resizeDocks({ this->commandDock }, { resizeEvent->size().width() }, 
			Qt::Orientation::Horizontal);

		this->resizeDocks({ this->commandDock }, { resizeEvent->size().height() }, 
			Qt::Orientation::Vertical);
	}
	
	return QWidget::eventFilter(obj, event);
}


void ShCAD::ShowContextMenu(const QPoint &pos) {

	if (this->mdiArea->subWindowList().size() != 0)
		this->contextMenu->exec(mapToGlobal(pos));
}

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
	this->mdiArea->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);

	this->ribbon = new ShRibbonMenu(150, this);
	this->ribbon->setWindowTitle("RibbonBar");
	this->addToolBar(Qt::ToolBarArea::TopToolBarArea, this->ribbon);
	this->ribbon->hide();
	this->addToolBarBreak();

	

	this->statusBar = new ShStatusBar(this);
	this->setStatusBar(this->statusBar);
	this->statusBar->hide();
	

	this->commandDock = new ShCommandDock(this);
	this->commandDock->installEventFilter(this);
	this->commandDock->setWindowTitle("Command");
	this->commandDock->hide();
	
	

	ShChangeManager *manager = ShChangeManager::GetInstance();
	manager->Register(this->statusBar);
	manager->Register(this->commandDock);

	this->toolBarContainer = new ShToolBarContainer(this);

}

void ShCAD::ActivateWidgets() {

	this->menuBar->ActivateMenu();

	this->setCentralWidget(this->mdiArea);
	this->mdiArea->show();

	this->ribbon->show();
	
	this->statusBar->show();
	
	this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, this->commandDock);
	this->commandDock->show();

	this->toolBarContainer->Activate();

}

void ShCAD::DeActivateWidgets() {

	this->menuBar->DeActivateMenu();

	this->takeCentralWidget();
	this->ribbon->hide();
	this->statusBar->hide();
	this->removeDockWidget(this->commandDock);

	this->toolBarContainer->DeActivate();

}