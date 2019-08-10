
#include "ShQuickAccessToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "Manager\ShLanguageManager.h"
#include "Chain of Responsibility\ShRequest.h"
#include <qpushbutton.h>
#include "Event\ShToolBarContainerEventFilter.h"

ShQuickAccessToolBar::ShQuickAccessToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("QuickAccessToolBar");

	this->setIconSize(QSize(20, 20));

	QAction *action = this->addAction(ShIcon(":/Image/File/New.png"), shGetLanValue_ui("File/New"));
	connect(action, &QAction::triggered, this, &ShQuickAccessToolBar::newActionClicked);

	this->addSeparator();

	this->undoButton = new QPushButton("undo", this);
	this->addWidget(this->undoButton);
	this->redoButton = new QPushButton("redo", this);
	this->addWidget(this->redoButton);

}

ShQuickAccessToolBar::~ShQuickAccessToolBar() {

}

void ShQuickAccessToolBar::update(ShNotifyEvent *event) {

	ShQuickAccessToolBarEventFilter filter(this, event);
	filter.update();
}

void ShQuickAccessToolBar::setUndoButtonEnabled(bool enabled) {

	this->undoButton->setEnabled(enabled);
}

void ShQuickAccessToolBar::setRedoButtonEnabled(bool enabled) {

	this->redoButton->setEnabled(enabled);
}

void ShQuickAccessToolBar::newActionClicked() {

	ShCreateNewCADWidgetRequest request;
	this->request(&request);
}