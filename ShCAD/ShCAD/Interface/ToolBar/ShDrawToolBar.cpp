

#include "ShDrawToolBar.h"
#include "Interface\Item\ShIcon.h"

ShDrawToolBar::ShDrawToolBar(const QString &title, QWidget *parent)
	:ShAbstractToolBar(title, parent) {

	this->setIconSize(QSize(20, 20));

	QAction *action = this->addAction(ShIcon(":/Image/Draw/Line.png"), "Line");
	action->setToolTip("Line \nCreates straight line segments");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::lineActionClicked);

	action = this->addAction(ShIcon(":/Image/Draw//PolyLine/PolyLine.png"), "PolyLine");
	action->setToolTip("PolyLine \nCreates a polyline");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::polyLineActionClicked);

	action = this->addAction(ShIcon(":/Image/Draw/Circle/Center-Radius.png"), "Circle");
	action->setToolTip("Circle \nCreates a circle using a center point and a radius");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::circleActionClicked);

	action = this->addAction(ShIcon(":/Image/Draw/Arc/3Point.png"), "Arc");
	action->setToolTip("Arc \nCreates an arc using three points");
	connect(action, &QAction::triggered, this, &ShDrawToolBar::arcActionClicked);

}

ShDrawToolBar::~ShDrawToolBar() {


}


void ShDrawToolBar::lineActionClicked() {


}

void ShDrawToolBar::polyLineActionClicked() {


}

void ShDrawToolBar::circleActionClicked() {


}

void ShDrawToolBar::arcActionClicked() {


}