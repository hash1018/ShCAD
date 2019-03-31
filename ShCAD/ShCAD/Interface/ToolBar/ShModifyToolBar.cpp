

#include "ShModifyToolBar.h"
#include "ShDirectoryManager.h"

ShModifyToolBar::ShModifyToolBar(const QString &title, QWidget *parent)
	:ShAbstractToolBar(title, parent) {

	this->setIconSize(QSize(20, 20));

	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;

	QAction *action;

	this->GetIcon(path + "\\Modify\\Erase.png", icon);
	action = this->addAction(icon, "Erase");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::EraseActionClicked);

	this->GetIcon(path + "\\Modify\\Copy.png", icon);
	action = this->addAction(icon, "Copy");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::CopyActionClicked);

	this->GetIcon(path + "\\Modify\\Mirror.png", icon);
	action = this->addAction(icon, "Mirror");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::MirrorActionClicked);

	this->GetIcon(path + "\\Modify\\Move.png", icon);
	action = this->addAction(icon, "Move");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::MoveActionClicked);

	this->GetIcon(path + "\\Modify\\Rotate.png", icon);
	action = this->addAction(icon, "Rotate");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::RotateActionClicked);

	this->GetIcon(path + "\\Modify\\Scale.png", icon);
	action = this->addAction(icon, "Scale");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::ScaleActionClicked);

	this->GetIcon(path + "\\Modify\\Stretch.png", icon);
	action = this->addAction(icon, "Stretch");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::StretchActionClicked);

	this->GetIcon(path + "\\Modify\\Extend.png", icon);
	action = this->addAction(icon, "Extend");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::ExtendActionClicked);

	this->GetIcon(path + "\\Modify\\Trim.png", icon);
	action = this->addAction(icon, "Trim");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::TrimActionClicked);
	
	
}

ShModifyToolBar::~ShModifyToolBar() {


}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Singleton Pattern\ShWidgetManager.h"
#include "Interface\ShGraphicView.h"
void ShModifyToolBar::EraseActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyErase);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::CopyActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyCopy);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::MirrorActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyMirror);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::MoveActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyMove);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::RotateActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyRotate);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::ScaleActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyScale);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::StretchActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyStretch);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::ExtendActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyExtend);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyToolBar::TrimActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyTrim);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}