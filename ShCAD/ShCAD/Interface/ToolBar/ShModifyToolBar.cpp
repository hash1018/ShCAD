

#include "ShModifyToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Chain of Responsibility\ShRequest.h"

ShModifyToolBar::ShModifyToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("ModifyToolBar");
	this->setIconSize(QSize(20, 20));

	QAction *action;

	action = this->addAction(ShIcon(":/Image/Modify/Erase.png"), "Erase");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::eraseActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Copy.png"), "Copy");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::copyActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Mirror.png"), "Mirror");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::mirrorActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Move.png"), "Move");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::moveActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Rotate.png"), "Rotate");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::rotateActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Scale.png"), "Scale");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::scaleActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Stretch.png"), "Stretch");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::stretchActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Extend.png"), "Extend");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::extendActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Trim.png"), "Trim");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::trimActionClicked);


}

ShModifyToolBar::~ShModifyToolBar() {


}

void ShModifyToolBar::eraseActionClicked() {


}

void ShModifyToolBar::copyActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyCopy);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyToolBar::mirrorActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyMirror);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyToolBar::moveActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyMove);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyToolBar::rotateActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyRotate);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyToolBar::scaleActionClicked() {


}

void ShModifyToolBar::stretchActionClicked() {


}

void ShModifyToolBar::extendActionClicked() {


}

void ShModifyToolBar::trimActionClicked() {


}