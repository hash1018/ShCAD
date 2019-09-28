
#include "ShDimensionToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Chain of Responsibility\ShRequest.h"

ShDimensionToolBar::ShDimensionToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("DimensionToolBar");
	this->setIconSize(QSize(20, 20));

	QAction *action = this->addAction(ShIcon(":/Image/Dimension/DimLinear.png"), "DimLinear");
	connect(action, &QAction::triggered, this, &ShDimensionToolBar::dimLinearActionClicked);

	action = this->addAction(ShIcon(":/Image/Dimension/DimAligned.png"), "DimAligned");
	connect(action, &QAction::triggered, this, &ShDimensionToolBar::dimAlignedActionClicked);

	action = this->addAction(ShIcon(":/Image/Dimension/DimArcLength.png"), "DimArcLength");
	connect(action, &QAction::triggered, this, &ShDimensionToolBar::dimArcLengthActionClicked);

	action = this->addAction(ShIcon(":/Image/Dimension/DimRadius.png"), "DimRadius");
	connect(action, &QAction::triggered, this, &ShDimensionToolBar::dimRadiusActionClicked);

	action = this->addAction(ShIcon(":/Image/Dimension/DimDiameter.png"), "DimDiameter");
	connect(action, &QAction::triggered, this, &ShDimensionToolBar::dimDiameterActionClicked);

	action = this->addAction(ShIcon(":/Image/Dimension/DimAngular.png"), "DimAngular");
	connect(action, &QAction::triggered, this, &ShDimensionToolBar::dimAngularActionClicked);
}

ShDimensionToolBar::~ShDimensionToolBar() {

}

void ShDimensionToolBar::dimLinearActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimLinear);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimensionToolBar::dimAlignedActionClicked() {

}

void ShDimensionToolBar::dimAngularActionClicked() {

}

void ShDimensionToolBar::dimRadiusActionClicked() {

}

void ShDimensionToolBar::dimDiameterActionClicked() {

}

void ShDimensionToolBar::dimArcLengthActionClicked() {

}