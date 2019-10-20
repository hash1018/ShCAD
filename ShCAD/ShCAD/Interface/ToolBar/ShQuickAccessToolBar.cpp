
#include "ShQuickAccessToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "Manager\ShLanguageManager.h"
#include "Chain of Responsibility\ShRequest.h"
#include <qpushbutton.h>
#include "Event\ToolBarEventFilter\ShQuickAccessToolBarEventFilter.h"

ShQuickAccessToolBar::ShQuickAccessToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("QuickAccessToolBar");

	this->setIconSize(QSize(20, 20));

	QAction *action = this->addAction(ShIcon(":/Image/File/New.png"), shGetLanValue_ui("File/New"));
	
	this->addSeparator();

	this->undoButton = new QPushButton(ShIcon(":/Image/Undo.png"), "", this);
	this->addWidget(this->undoButton);
	this->redoButton = new QPushButton(ShIcon(":/Image/Redo.png"), "", this);
	this->addWidget(this->redoButton);


	connect(action, &QAction::triggered, this, &ShQuickAccessToolBar::newActionClicked);
	connect(this->undoButton, &QPushButton::pressed, this, &ShQuickAccessToolBar::undoButtonClicked);
	connect(this->redoButton, &QPushButton::pressed, this, &ShQuickAccessToolBar::redoButtonClicked);
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

	ShRequestCreateNewCADWidget request;
	this->request(&request);
}

void ShQuickAccessToolBar::undoButtonClicked() {

	ShRequestUndo request;
	this->request(&request);
}

void ShQuickAccessToolBar::redoButtonClicked() {

	ShRequestRedo request;
	this->request(&request);
}