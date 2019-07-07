

#include "ShMenu.h"
#include "Interface\Item\ShIcon.h"
#include "ShMenuBar.h"
#include <qdebug.h>

ShAbstractMenu::ShAbstractMenu(const QString &title, ShMenuBar *parent)
	:QMenu(title, parent) {

}

ShAbstractMenu::~ShAbstractMenu() {

}

///////////////////////////////////////////////////////////////////////////

ShEmptyDrawingFileMenu::ShEmptyDrawingFileMenu(const QString &title, ShMenuBar *parent)
	:ShAbstractMenu(title, parent) {

	this->newAction = new QAction(ShIcon(":/Image/File/New.png"), "New", this);

	this->addAction(this->newAction);

	if (this->parent == nullptr) {
		qDebug() << "ShEmptyDrawingFileMenu::ShEmptyDrawingFileMenu  parent is nullptr";
		return;
	}
	
	connect(this->newAction, &QAction::triggered, parent, &ShMenuBar::newActionClicked);
}

ShEmptyDrawingFileMenu::~ShEmptyDrawingFileMenu() {

}

///////////////////////////////////////////////////////////////////////////

ShFileMenu::ShFileMenu(const QString &title, ShMenuBar *parent)
	:ShAbstractMenu(title, parent) {

	this->newAction = new QAction(ShIcon(":/Image/File/New.png"), "New", this);
	this->addAction(this->newAction);

	this->addSeparator();

	this->plotAction = new QAction(ShIcon(":/Image/File/Print.png"), "Plot", this);
	this->addAction(this->plotAction);

	this->previewAction = new QAction(ShIcon(":/Image/File/Preview.png"), "Preview", this);
	this->addAction(this->previewAction);

	if (this->parent == nullptr) {
		qDebug() << "ShFileMenu::ShFileMenu  parent is nullptr";
		return;
	}
	
	connect(this->newAction, &QAction::triggered, parent, &ShMenuBar::newActionClicked);
}

ShFileMenu::~ShFileMenu() {

}

/////////////////////////////////////////////////////////////////////////

ShEditMenu::ShEditMenu(const QString &title, ShMenuBar *parent)
	:ShAbstractMenu(title, parent) {

}

ShEditMenu::~ShEditMenu() {

}


/////////////////////////////////////////////////////////////////////////

ShDrawMenu::ShDrawMenu(const QString &title, ShMenuBar *parent)
	:ShAbstractMenu(title, parent) {

	this->lineAction = new QAction(ShIcon(":/Image/Draw/Line.png"), "Line", this);
	this->addAction(this->lineAction);

	this->addSeparator();

	this->polyLineAction = new QAction(ShIcon(":/Image/Draw/PolyLine/PolyLine.png"), "PolyLine", this);
	this->addAction(this->polyLineAction);

	this->polygonAction = new QAction(ShIcon(":/Image/Draw/PolyLine/Polygon.png"), "Polygon", this);
	this->addAction(this->polygonAction);

	this->rectangleAction = new QAction(ShIcon(":/Image/Draw/PolyLine/Rectangle.png"), "Rectangle", this);
	this->addAction(this->rectangleAction);

	this->addSeparator();


	this->createCircleMenu();

	this->addSeparator();

	this->createArcMenu();
}

ShDrawMenu::~ShDrawMenu() {

}

void ShDrawMenu::createCircleMenu() {

	this->circleMenu = new QMenu("Circle", this);
	this->addMenu(this->circleMenu);

	this->circleCenterRadiusAction = new QAction(ShIcon(":/Image/Draw/Circle/Center-Radius.png"), "Center, Radius", this->circleMenu);
	this->circleMenu->addAction(this->circleCenterRadiusAction);

	this->circleCenterDiameterAction = new QAction(ShIcon(":/Image/Draw/Circle/Center-Diameter.png"), "Center, Diameter", this->circleMenu);
	this->circleMenu->addAction(this->circleCenterDiameterAction);


	this->circleMenu->addSeparator();

	this->circleTwoPointAction = new QAction(ShIcon(":/Image/Draw/Circle/2Point.png"), "2 Points", this->circleMenu);
	this->circleMenu->addAction(this->circleTwoPointAction);

	this->circleThreePointAction = new QAction(ShIcon(":/Image/Draw/Circle/3Point.png"), "3 Points", this->circleMenu);
	this->circleMenu->addAction(this->circleThreePointAction);

}

void ShDrawMenu::createArcMenu() {

	this->arcMenu = new QMenu("Arc", this);
	this->addMenu(this->arcMenu);

	this->arcThreePointAction = new QAction(ShIcon(":/Image/Draw/Arc/3Point.png"), "3 Points", this->arcMenu);
	this->arcMenu->addAction(this->arcThreePointAction);


	this->arcMenu->addSeparator();

	this->arcStartCenterEndAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-Center-End.png"), "Start, Center, End", this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterEndAction);

	this->arcStartCenterAngleAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-Center-Angle.png"), "Start, Center, Angle", this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterAngleAction);

	this->arcStartCenterLengthAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-Center-Length.png"), "Start, Center, Length", this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterLengthAction);


	this->arcMenu->addSeparator();

	this->arcStartEndAngleAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-End-Angle.png"), "Start, End, Angle", this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndAngleAction);

	this->arcStartEndDirectionAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-End-Direction.png"), "Start, End, Direction", this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndDirectionAction);

	this->arcStartEndRadiusAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-End-Radius.png"), "Start, End, Radius", this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndRadiusAction);


	this->arcMenu->addSeparator();

	this->arcCenterStartEndAction = new QAction(ShIcon(":/Image/Draw/Arc/Center-Start-End.png"), "Center, Start, End", this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartEndAction);

	this->arcCenterStartAngleAction = new QAction(ShIcon(":/Image/Draw/Arc/Center-Start-Angle.png"), "Center, Start, Angle", this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartAngleAction);

	this->arcCenterStartLengthAction = new QAction(ShIcon(":/Image/Draw/Arc/Center-Start-Length.png"), "Center, Start, Length", this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartLengthAction);
}

/////////////////////////////////////////////////////////////////////////

ShModifyMenu::ShModifyMenu(const QString &title, ShMenuBar *parent)
	:ShAbstractMenu(title, parent) {

	this->eraseAction = new QAction(ShIcon(":/Image/Modify/Erase.png"), "Erase", this);
	this->addAction(this->eraseAction);

	this->copyAction = new QAction(ShIcon(":/Image/Modify/Copy.png"), "Copy", this);
	this->addAction(this->copyAction);

	this->mirrorAction = new QAction(ShIcon(":/Image/Modify/Mirror.png"), "Mirror", this);
	this->addAction(this->mirrorAction);

	this->addSeparator();

	this->moveAction = new QAction(ShIcon(":/Image/Modify/Move.png"), "Move", this);
	this->addAction(this->moveAction);

	this->rotateAction = new QAction(ShIcon(":/Image/Modify/Rotate.png"), "Rotate", this);
	this->addAction(this->rotateAction);

	this->scaleAction = new QAction(ShIcon(":/Image/Modify/Scale.png"), "Scale", this);
	this->addAction(this->scaleAction);

	this->stretchAction = new QAction(ShIcon(":/Image/Modify/Stretch.png"), "Stretch", this);
	this->addAction(this->stretchAction);

	this->addSeparator();

	this->trimAction = new QAction(ShIcon(":/Image/Modify/Trim.png"), "Trim", this);
	this->addAction(this->trimAction);

	this->extendAction = new QAction(ShIcon(":/Image/Modify/Extend.png"), "Extend", this);
	this->addAction(this->extendAction);
}

ShModifyMenu::~ShModifyMenu() {

}