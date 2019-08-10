

#include "ShCAD.h"
#include <qmdiarea.h>
#include "Dock\ShCommandDock.h"
#include <QEvent>
#include <QResizeEvent>
#include <qmenu.h>
#include "Menu\ShMenuBar.h"
#include "Manager\ShCADWidgetManager.h"
#include "ShCADWidget.h"
#include "Ribbon\ShRibbonMenu.h"
#include "StatusBar\ShStatusBar.h"
#include "ToolBar\ShToolBarContainer.h"
#include "Manager\ShChangeManager.h"
#include "Chain of Responsibility\ShRequest.h"
#include <qsettings.h>


ShCAD::ShCAD(QWidget *parent)
	: QMainWindow(parent){
	
	this->initWidgets();
	this->registerObservers();
	this->createCADWidget();
	this->createContextMenu();

	this->readSettings();

	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContexMenu(const QPoint &)));
	connect(this->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(subActivateWindowChanged(QMdiSubWindow*)));

}

ShCAD::~ShCAD(){

	if (this->mdiArea != nullptr)
		delete this->mdiArea;

	if (this->toolBarContainer != nullptr)
		delete this->toolBarContainer;
	
}


void ShCAD::initWidgets() {

	this->menuBar = new ShMenuBar(this, this);
	this->setMenuBar(this->menuBar);

	this->commandDock = new ShCommandDock(this, this);
	this->commandDock->installEventFilter(this);
	this->commandDock->hide();

	this->mdiArea = new QMdiArea;
	this->mdiArea->setDocumentMode(true);
	this->mdiArea->hide();
	this->mdiArea->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);

	this->ribbonMenu = new ShRibbonMenu(150, this, this);
	this->addToolBar(Qt::ToolBarArea::TopToolBarArea, this->ribbonMenu);
	this->ribbonMenu->hide();
	this->addToolBarBreak();

	this->statusBar = new ShStatusBar(this);
	this->setStatusBar(this->statusBar);
	this->statusBar->hide();
	
	this->toolBarContainer = new ShToolBarContainer(this, this);

	
	
}

void ShCAD::registerObservers() {

	ShChangeManager *manager = ShChangeManager::getInstance();

	manager->registerObserver(this->statusBar);
	manager->registerObserver(this->commandDock);
	manager->registerObserver(this->ribbonMenu);
	manager->registerObserver(this->toolBarContainer);
}

void ShCAD::activateWidgets() {

	this->menuBar->activateMenu();

	this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, this->commandDock);
	this->commandDock->activate();

	this->setCentralWidget(this->mdiArea);
	this->mdiArea->show();

	this->ribbonMenu->activate();

	this->statusBar->show();

	this->toolBarContainer->activate();
}

void ShCAD::deactivateWidgets() {

	this->menuBar->deactivateMenu();

	this->takeCentralWidget();

	this->removeDockWidget(this->commandDock);
	this->commandDock->deactivate();

	this->ribbonMenu->deactivate();

	this->statusBar->hide();

	this->toolBarContainer->deactivate();
}

void ShCAD::createCADWidget() {

	if (this->mdiArea->subWindowList().size() == 0) {
		this->activateWidgets();
	}

	ShCADWidget *cadWidget = new ShCADWidget(this->mdiArea);
	cadWidget->setMinimumSize(400, 400);

	this->mdiArea->addSubWindow(cadWidget, Qt::WindowFlags::enum_type::SubWindow);
	cadWidget->showMaximized();

	ShCADWidgetManager::getInstance()->add(cadWidget);
}

void ShCAD::request(ShRequest *request) {

	if (request->getType() == ShRequest::RequestType::RequestCreateNewCADWidget)
		this->createCADWidget();
	else if (request->getType() == ShRequest::RequestChangeActionHandler) {

		if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
			return;
		ShRequestChangeActionHandler *request2 = dynamic_cast<ShRequestChangeActionHandler*>(request);
		ShCADWidgetManager::getInstance()->getActivatedWidget()->changeAction(*(request2->getStrategy()));
	}
	else if (request->getType() == ShRequest::RequestSendNotifyEvent) {

		if (ShCADWidgetManager::getInstance()->getActivatedWidget() == nullptr)
			return;

		ShRequestSendNotifyEvent *request2 = dynamic_cast<ShRequestSendNotifyEvent*>(request);
		ShCADWidgetManager::getInstance()->getActivatedWidget()->update(request2->getNotifyEvent());
	}

}

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

void ShCAD::closeEvent(QCloseEvent *event) {

	this->writeSettings();

	QMainWindow::closeEvent(event);

}

void ShCAD::createContextMenu() {

	this->contextMenu = new QMenu("ContextMenu", this);
	this->contextMenu->addAction(this->ribbonMenu->getMenuAction());
	this->contextMenu->addAction(this->commandDock->getMenuAction());
	this->contextMenu->addMenu(this->toolBarContainer->getToolBarMenu());
}

void ShCAD::readSettings() {

	QSettings settings("SeungHo Ha", "ShCAD");

	settings.beginGroup("MainWindow");
	
	this->restoreGeometry(settings.value("geometry", this->saveGeometry()).toByteArray());
	this->restoreState(settings.value("state", this->saveState()).toByteArray());
	this->move(settings.value("pos", this->pos()).toPoint());
	this->resize(settings.value("size", this->size()).toSize());

	if (settings.value("maximized", this->isMaximized()).toBool() == true)
		this->showMaximized();

	settings.endGroup();

	this->toolBarContainer->readSettings();
}

void ShCAD::writeSettings() {

	QSettings settings("SeungHo Ha", "ShCAD");

	settings.beginGroup("MainWindow");

	settings.setValue("geometry", this->saveGeometry());
	settings.setValue("state", this->saveState());
	settings.setValue("maximized", this->isMaximized());
	
	if (this->isMaximized() == false) {
		settings.setValue("pos", this->pos());
		settings.setValue("size", this->size());
	}
	
	settings.endGroup();

	this->toolBarContainer->writeSettings();
}

void ShCAD::subActivateWindowChanged(QMdiSubWindow*) {

	if (this->mdiArea->subWindowList().size() == 0)
		this->deactivateWidgets();
}

void ShCAD::showContexMenu(const QPoint &pos) {

	if (this->mdiArea->subWindowList().size() != 0)
		this->contextMenu->exec(mapToGlobal(pos));
}

