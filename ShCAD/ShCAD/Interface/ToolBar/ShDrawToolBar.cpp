
#include "ShDrawToolBar.h"
#include "ShDirectoryManager.h"

ShDrawToolBar::ShDrawToolBar(const QString &title, QWidget *parent)
	:ShAbstractToolBar(title, parent) {

	this->setIconSize(QSize(20, 20));

	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;

	this->GetIcon(path + "\\Line.png", icon);
	QAction *action = this->addAction(icon, "Line");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::LineActionClicked);

	this->GetIcon(path + "\\PolyLine\\PolyLine.png", icon);
	action = this->addAction(icon, "PolyLine");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::PolyLineActionClicked);

	this->GetIcon(path + "\\Circle\\Center-Radius.png", icon);
	action = this->addAction(icon, "Circle");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::CircleActionClicked);

	this->GetIcon(path + "\\Arc\\3Point.png", icon);
	action = this->addAction(icon, "Arc");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::ArcActionClicked);

}

ShDrawToolBar::~ShDrawToolBar() {


}


#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Singleton Pattern\ShWidgetManager.h"
#include "Interface\ShGraphicView.h"
void ShDrawToolBar::LineActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawLine);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawToolBar::PolyLineActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawPolyLine);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawToolBar::CircleActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleCenterRadius);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawToolBar::ArcActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcThreePoint);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}