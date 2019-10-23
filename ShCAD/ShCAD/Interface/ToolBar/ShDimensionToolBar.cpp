
#include "ShDimensionToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Chain of Responsibility\ShRequest.h"
#include "Interface\Item\ShDimensionStyleComboBox.h"
#include <qpushbutton.h>
#include "Event\ToolBarEventFilter\ShDimensionToolBarEventFilter.h"
#include "Event\ShNotifyEvent.h"

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

	this->addSeparator();

	this->dimensionStyleComboBox = new ShDimensionStyleComboBox(this);
	this->addWidget(this->dimensionStyleComboBox);
	connect(this->dimensionStyleComboBox, &ShDimensionStyleComboBox::currentDimensionStyleChanged, this, &ShDimensionToolBar::currentDimensionStyleChanged);

	action = this->addAction(ShIcon(":/Image/Dimension/DimStyleSetting.png"), "DimStyle");
	connect(action, &QAction::triggered, this, &ShDimensionToolBar::modifyDimensionStyleActionClicked);
	
}

ShDimensionToolBar::~ShDimensionToolBar() {

}

void ShDimensionToolBar::update(ShNotifyEvent *event) {

	ShDimensionToolBarEventFilter filter(this, event);
	filter.update();
}

void ShDimensionToolBar::dimLinearActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimLinear);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimensionToolBar::dimAlignedActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimAligned);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimensionToolBar::dimAngularActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimAngular);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimensionToolBar::dimRadiusActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimRadius);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimensionToolBar::dimDiameterActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimDiameter);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimensionToolBar::dimArcLengthActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimArcLength);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimensionToolBar::currentDimensionStyleChanged(ShDimensionStyle *dimensionStyle) {

	ShCurrentDimensionStyleChangedEvent event(dimensionStyle);
	ShRequestSendNotifyEvent request(&event);
	this->request(&request);
}

void ShDimensionToolBar::modifyDimensionStyleActionClicked() {

}