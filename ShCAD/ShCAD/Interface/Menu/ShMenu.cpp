

#include "ShMenu.h"
#include "ShMenuBar.h"
#include "ShDirectoryManager.h"
#include "Singleton Pattern\ShWidgetManager.h"


ShAbstractMenu::ShAbstractMenu(const QString &title, QWidget *parent)
	:QMenu(title, parent) {

}

ShAbstractMenu::~ShAbstractMenu() {


}

#include <qbitmap.h>
QIcon ShAbstractMenu::GetIcon(const QString &filePath) {

	QPixmap pix(filePath);
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);

	return icon;
}



ShEmptyDrawingFileMenu::ShEmptyDrawingFileMenu(const QString &title, QWidget *parent)
	:ShAbstractMenu(title, parent) {
	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;

	icon = this->GetIcon(path + "\\Utility\\New.png");
	this->newAction = new QAction(icon, "New", this);

	this->addAction(this->newAction);

	ShMenuBar *menuBar = dynamic_cast<ShMenuBar*>(this->parent());
	connect(this->newAction, &QAction::triggered, menuBar, &ShMenuBar::NewActionClicked);

}

ShEmptyDrawingFileMenu::~ShEmptyDrawingFileMenu() {

}

///////////////////////////////////////////////////////////////////////////////////////

ShFileMenu::ShFileMenu(const QString &title, QWidget *parent)
	:ShAbstractMenu(title, parent) {

	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;

	icon = this->GetIcon(path + "\\Utility\\New.png");
	this->newAction = new QAction(icon, "New", this);
	this->addAction(this->newAction);

	this->addSeparator();

	icon = this->GetIcon(path + "\\Utility\\Print.png");
	this->plotAction = new QAction(icon, "Plot", this);
	this->addAction(this->plotAction);

	icon = this->GetIcon(path + "\\Utility\\Preview.png");
	this->previewAction = new QAction(icon, "Preview", this);
	this->addAction(this->previewAction);

	ShMenuBar *menuBar = dynamic_cast<ShMenuBar*>(this->parent());
	connect(this->newAction, &QAction::triggered, menuBar, &ShMenuBar::NewActionClicked);
	connect(this->plotAction, &QAction::triggered, this, &ShFileMenu::PlotActionClicked);
	connect(this->previewAction, &QAction::triggered, this, &ShFileMenu::PreviewActionClicked);

	
}

ShFileMenu::~ShFileMenu() {


}

#include "Interface\Dialog\ShPlotDialog.h"
void ShFileMenu::PlotActionClicked() {

	ShPlotDialog *dialog = new ShPlotDialog(this);
	dialog->exec();
}

#include "Singleton Pattern\ShPrinterManager.h"
#include "Interface\Dialog\ShPreviewDialog.h"
void ShFileMenu::PreviewActionClicked() {

	if (ShPrinterManager::GetInstance()->IsSavedInfo() == false)
		return;

	ShPreviewDialog previewDlg(this);
	previewDlg.exec();
}

/////////////////////////////////////////////////////////////////////////////////////////

ShEditMenu::ShEditMenu(const QString &title, QWidget *parent)
	:ShAbstractMenu(title, parent) {

}

ShEditMenu::~ShEditMenu() {


}

////////////////////////////////////////////////////////////////////////////////////////

ShDrawMenu::ShDrawMenu(const QString &title, QWidget *parent)
	:ShAbstractMenu(title, parent) {
	
	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;


	icon = this->GetIcon(path + "\\Line.png");
	this->lineAction = new QAction(icon, "Line", this);
	this->addAction(this->lineAction);
	connect(this->lineAction, &QAction::triggered, this, &ShDrawMenu::LineActionClicked);

	this->addSeparator();

	icon = this->GetIcon(path + "\\PolyLine\\PolyLine.png");
	this->polyLineAction = new QAction(icon, "PolyLine", this);
	this->addAction(this->polyLineAction);
	connect(this->polyLineAction, &QAction::triggered, this, &ShDrawMenu::PolyLineActionClicked);

	icon = this->GetIcon(path + "\\PolyLine\\Polygon.png");
	this->polygonAction = new QAction(icon, "Polygon", this);
	this->addAction(this->polygonAction);
	connect(this->polygonAction, &QAction::triggered, this, &ShDrawMenu::PolygonActionClicked);

	icon = this->GetIcon(path + "\\PolyLine\\Rectangle.png");
	this->rectangleAction = new QAction(icon, "Rectangle", this);
	this->addAction(this->rectangleAction);
	connect(this->rectangleAction, &QAction::triggered, this, &ShDrawMenu::RectangleActionClicked);

	this->addSeparator();


	this->CreateCircleMenu();
	
	this->addSeparator();

	this->CreateArcMenu();

}

ShDrawMenu::~ShDrawMenu() {


}

void ShDrawMenu::CreateCircleMenu() {

	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;

	this->circleMenu = new QMenu("Circle", this);
	this->addMenu(this->circleMenu);

	icon = this->GetIcon(path + "\\Circle\\Center-Radius.png");
	this->circleCenterRadiusAction = new QAction(icon, "Center, Radius", this->circleMenu);
	this->circleMenu->addAction(this->circleCenterRadiusAction);

	icon = this->GetIcon(path + "\\Circle\\Center-Diameter.png");
	this->circleCenterDiameterAction = new QAction(icon, "Center, Diameter", this->circleMenu);
	this->circleMenu->addAction(this->circleCenterDiameterAction);


	this->circleMenu->addSeparator();


	icon = this->GetIcon(path + "\\Circle\\2Point.png");
	this->circleTwoPointAction = new QAction(icon, "2 Points", this->circleMenu);
	this->circleMenu->addAction(this->circleTwoPointAction);

	icon = this->GetIcon(path + "\\Circle\\3Point.png");
	this->circleThreePointAction = new QAction(icon, "3 Points", this->circleMenu);
	this->circleMenu->addAction(this->circleThreePointAction);


	connect(this->circleCenterRadiusAction, &QAction::triggered, this, &ShDrawMenu::CircleCenterRadiusClicked);
	connect(this->circleCenterDiameterAction, &QAction::triggered, this, &ShDrawMenu::CircleCenterDiameterClicked);
	connect(this->circleTwoPointAction, &QAction::triggered, this, &ShDrawMenu::CircleTwoPointClicked);
	connect(this->circleThreePointAction, &QAction::triggered, this, &ShDrawMenu::CircleThreePointClicked);
}

void ShDrawMenu::CreateArcMenu() {

	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;

	this->arcMenu = new QMenu("Arc", this);
	this->addMenu(this->arcMenu);

	icon = this->GetIcon(path + "\\Arc\\3Point.png");
	this->arcThreePointAction = new QAction(icon, "3 Points", this->arcMenu);
	this->arcMenu->addAction(this->arcThreePointAction);


	this->arcMenu->addSeparator();


	icon = this->GetIcon(path + "\\Arc\\Start-Center-End.png");
	this->arcStartCenterEndAction = new QAction(icon, "Start, Center, End", this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterEndAction);

	icon = this->GetIcon(path + "\\Arc\\Start-Center-Angle.png");
	this->arcStartCenterAngleAction = new QAction(icon, "Start, Center, Angle", this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterAngleAction);

	icon = this->GetIcon(path + "\\Arc\\Start-Center-Length.png");
	this->arcStartCenterLengthAction = new QAction(icon, "Start, Center, Length", this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterLengthAction);


	this->arcMenu->addSeparator();

	icon = this->GetIcon(path + "\\Arc\\Start-End-Angle.png");
	this->arcStartEndAngleAction = new QAction(icon, "Start, End, Angle", this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndAngleAction);

	icon = this->GetIcon(path + "\\Arc\\Start-End-Direction.png");
	this->arcStartEndDirectionAction = new QAction(icon, "Start, End, Direction", this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndDirectionAction);

	icon = this->GetIcon(path + "\\Arc\\Start-End-Radius.png");
	this->arcStartEndRadiusAction = new QAction(icon, "Start, End, Radius", this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndRadiusAction);


	this->arcMenu->addSeparator();

	icon = this->GetIcon(path + "\\Arc\\Center-Start-End.png");
	this->arcCenterStartEndAction = new QAction(icon, "Center, Start, End", this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartEndAction);

	icon = this->GetIcon(path + "\\Arc\\Center-Start-Angle.png");
	this->arcCenterStartAngleAction = new QAction(icon, "Center, Start, Angle", this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartAngleAction);
	
	icon = this->GetIcon(path + "\\Arc\\Center-Start-Length.png");
	this->arcCenterStartLengthAction = new QAction(icon, "Center, Start, Length", this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartLengthAction);

	
	connect(this->arcThreePointAction, &QAction::triggered, this, &ShDrawMenu::ArcThreePointClicked);

	connect(this->arcStartCenterEndAction, &QAction::triggered, this, &ShDrawMenu::ArcStartCenterEndClicked);
	connect(this->arcStartCenterAngleAction, &QAction::triggered, this, &ShDrawMenu::ArcStartCenterAngleClicked);
	connect(this->arcStartCenterLengthAction, &QAction::triggered, this, &ShDrawMenu::ArcStartCenterLengthClicked);

	connect(this->arcStartEndAngleAction, &QAction::triggered, this, &ShDrawMenu::ArcStartEndAngleClicked);
	connect(this->arcStartEndDirectionAction, &QAction::triggered, this, &ShDrawMenu::ArcStartEndDirectionClicked);
	connect(this->arcStartEndRadiusAction, &QAction::triggered, this, &ShDrawMenu::ArcStartEndRadiusClicked);

	connect(this->arcCenterStartEndAction, &QAction::triggered, this, &ShDrawMenu::ArcCenterStartEndClicked);
	connect(this->arcCenterStartAngleAction, &QAction::triggered, this, &ShDrawMenu::ArcCenterStartAngleClicked);
	connect(this->arcCenterStartLengthAction, &QAction::triggered, this, &ShDrawMenu::ArcCenterStartLengthClicked);

}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Interface\ShGraphicView.h"
void ShDrawMenu::LineActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawLine);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);

}

void ShDrawMenu::PolyLineActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawPolyLine);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::PolygonActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawPolygon);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::RectangleActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawRectangle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);

}

void ShDrawMenu::CircleCenterRadiusClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleCenterRadius);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::CircleCenterDiameterClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleCenterDiameter);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::CircleTwoPointClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleTwoPoint);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::CircleThreePointClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawCircleThreePoint);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcThreePointClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcThreePoint);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcStartCenterEndClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartCenterEnd);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcStartCenterAngleClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartCenterAngle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcStartCenterLengthClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartCenterLength);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);

}

void ShDrawMenu::ArcStartEndAngleClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartEndAngle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcStartEndDirectionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartEndDirection);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcStartEndRadiusClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcStartEndRadius);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcCenterStartEndClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcCenterStartEnd);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShDrawMenu::ArcCenterStartAngleClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcCenterStartAngle);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);

}

void ShDrawMenu::ArcCenterStartLengthClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDrawArcCenterStartLength);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);

}


///////////////////////////////////////////////////////////////////////////////////////////


ShModifyMenu::ShModifyMenu(const QString &title, QWidget *parent)
	:ShAbstractMenu(title, parent) {

	QString path = ShDirectoryManager::GetImageUiPath();
	QIcon icon;

	icon = this->GetIcon(path + "\\Modify\\Erase.png");
	this->eraseAction = new QAction(icon, "Erase", this);
	this->addAction(this->eraseAction);

	icon = this->GetIcon(path + "\\Modify\\Copy.png");
	this->copyAction = new QAction(icon, "Copy", this);
	this->addAction(this->copyAction);

	icon = this->GetIcon(path + "\\Modify\\Mirror.png");
	this->mirrorAction = new QAction(icon, "Mirror", this);
	this->addAction(this->mirrorAction);

	this->addSeparator();

	icon = this->GetIcon(path + "\\Modify\\Move.png");
	this->moveAction = new QAction(icon, "Move", this);
	this->addAction(this->moveAction);

	icon = this->GetIcon(path + "\\Modify\\Rotate.png");
	this->rotateAction = new QAction(icon, "Rotate", this);
	this->addAction(this->rotateAction);

	icon = this->GetIcon(path + "\\Modify\\Scale.png");
	this->scaleAction = new QAction(icon, "Scale", this);
	this->addAction(this->scaleAction);

	icon = this->GetIcon(path + "\\Modify\\Stretch.png");
	this->stretchAction = new QAction(icon, "Stretch", this);
	this->addAction(this->stretchAction);

	this->addSeparator();

	icon = this->GetIcon(path + "\\Modify\\Trim.png");
	this->trimAction = new QAction(icon, "Trim", this);
	this->addAction(this->trimAction);

	icon = this->GetIcon(path + "\\Modify\\Extend.png");
	this->extendAction = new QAction(icon, "Extend", this);
	this->addAction(this->extendAction);




	connect(this->moveAction, &QAction::triggered, this, &ShModifyMenu::MoveActionClicked);
	connect(this->copyAction, &QAction::triggered, this, &ShModifyMenu::CopyActionClicked);
	connect(this->stretchAction, &QAction::triggered, this, &ShModifyMenu::StretchActionClicked);
	connect(this->rotateAction, &QAction::triggered, this, &ShModifyMenu::RotateActionClicked);
	connect(this->mirrorAction, &QAction::triggered, this, &ShModifyMenu::MirrorActionClicked);
	connect(this->scaleAction, &QAction::triggered, this, &ShModifyMenu::ScaleActionClicked);
	connect(this->eraseAction, &QAction::triggered, this, &ShModifyMenu::EraseActionClicked);
	connect(this->extendAction, &QAction::triggered, this, &ShModifyMenu::ExtendActionClicked);
	connect(this->trimAction, &QAction::triggered, this, &ShModifyMenu::TrimActionClicked);



}

ShModifyMenu::~ShModifyMenu() {

}


void ShModifyMenu::EraseActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyErase);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::CopyActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyCopy);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::MirrorActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyMirror);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::MoveActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyMove);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::RotateActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyRotate);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::ScaleActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyScale);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::StretchActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyStretch);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::TrimActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyTrim);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}

void ShModifyMenu::ExtendActionClicked() {

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionModifyExtend);
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(strategy);
}
