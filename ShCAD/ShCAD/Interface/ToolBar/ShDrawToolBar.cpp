

#include "ShDrawToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Chain of Responsibility\ShRequest.h"

ShDrawToolBar::ShDrawToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("DrawToolBar");
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

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawLine);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawToolBar::polyLineActionClicked() {


}

void ShDrawToolBar::circleActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleCenterRadius);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawToolBar::arcActionClicked() {


}