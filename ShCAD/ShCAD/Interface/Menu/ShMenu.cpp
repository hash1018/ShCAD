

#include "ShMenu.h"
#include "Interface\Item\ShIcon.h"
#include <qdebug.h>
#include "Manager\ShLanguageManager.h"
#include "Chain of Responsibility\ShRequest.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"

ShAbstractMenu::ShAbstractMenu(const QString &title, ShChain *chain, QWidget *parent)
	:QMenu(title, parent), ShChain(chain) {

}

ShAbstractMenu::~ShAbstractMenu() {

}

///////////////////////////////////////////////////////////////////////////

ShEmptyDrawingFileMenu::ShEmptyDrawingFileMenu(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractMenu(title, chain, parent) {

	this->newAction = new QAction(ShIcon(":/Image/File/New.png"), shGetLanValue_ui("File/New"), this);

	this->addAction(this->newAction);

	connect(this->newAction, &QAction::triggered, this, &ShEmptyDrawingFileMenu::newActionClicked);
}

ShEmptyDrawingFileMenu::~ShEmptyDrawingFileMenu() {

}

void ShEmptyDrawingFileMenu::newActionClicked() {
	
	ShRequestCreateNewCADWidget request;
	this->request(&request);
}

///////////////////////////////////////////////////////////////////////////

ShFileMenu::ShFileMenu(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractMenu(title, chain, parent) {

	this->newAction = new QAction(ShIcon(":/Image/File/New.png"), shGetLanValue_ui("File/New"), this);
	this->addAction(this->newAction);

	this->addSeparator();

	this->plotAction = new QAction(ShIcon(":/Image/File/Print.png"), shGetLanValue_ui("File/Plot"), this);
	this->addAction(this->plotAction);

	this->previewAction = new QAction(ShIcon(":/Image/File/Preview.png"), shGetLanValue_ui("File/Preview"), this);
	this->addAction(this->previewAction);


	connect(this->newAction, &QAction::triggered, this, &ShFileMenu::newActionClicked);
}

ShFileMenu::~ShFileMenu() {

}

void ShFileMenu::newActionClicked() {
	
	ShRequestCreateNewCADWidget request;
	this->request(&request);
}

/////////////////////////////////////////////////////////////////////////

ShEditMenu::ShEditMenu(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractMenu(title, chain, parent) {

}

ShEditMenu::~ShEditMenu() {

}


/////////////////////////////////////////////////////////////////////////

ShDrawMenu::ShDrawMenu(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractMenu(title, chain, parent) {

	this->lineAction = new QAction(ShIcon(":/Image/Draw/Line.png"),
		shGetLanValue_ui("Draw/Line"), this);
	this->addAction(this->lineAction);

	this->addSeparator();

	this->polyLineAction = new QAction(ShIcon(":/Image/Draw/PolyLine/PolyLine.png"),
		shGetLanValue_ui("Draw/PolyLine"), this);
	this->addAction(this->polyLineAction);

	this->polygonAction = new QAction(ShIcon(":/Image/Draw/PolyLine/Polygon.png"),
		shGetLanValue_ui("Draw/Polygon"), this);
	this->addAction(this->polygonAction);

	this->rectangleAction = new QAction(ShIcon(":/Image/Draw/PolyLine/Rectangle.png"),
		shGetLanValue_ui("Draw/Rectangle"), this);
	this->addAction(this->rectangleAction);

	this->addSeparator();


	this->createCircleMenu();

	this->addSeparator();

	this->createArcMenu();
	
	connect(this->lineAction, &QAction::triggered, this, &ShDrawMenu::lineActionClicked);
}

ShDrawMenu::~ShDrawMenu() {


}

void ShDrawMenu::createCircleMenu() {

	this->circleMenu = new QMenu(shGetLanValue_ui("Draw/Circle"), this);
	this->addMenu(this->circleMenu);

	this->circleCenterRadiusAction = new QAction(ShIcon(":/Image/Draw/Circle/Center-Radius.png"), 
		shGetLanValue_ui("Draw/Circle,Center,Radius"),this->circleMenu);
	this->circleMenu->addAction(this->circleCenterRadiusAction);

	this->circleCenterDiameterAction = new QAction(ShIcon(":/Image/Draw/Circle/Center-Diameter.png"), 
		shGetLanValue_ui("Draw/Circle,Center,Diameter"), this->circleMenu);
	this->circleMenu->addAction(this->circleCenterDiameterAction);


	this->circleMenu->addSeparator();

	this->circleTwoPointAction = new QAction(ShIcon(":/Image/Draw/Circle/2Point.png"), 
		shGetLanValue_ui("Draw/Circle,TwoPoints"), this->circleMenu);
	this->circleMenu->addAction(this->circleTwoPointAction);

	this->circleThreePointAction = new QAction(ShIcon(":/Image/Draw/Circle/3Point.png"), 
		shGetLanValue_ui("Draw/Circle,ThreePoints"), this->circleMenu);
	this->circleMenu->addAction(this->circleThreePointAction);

	connect(this->circleCenterRadiusAction, &QAction::triggered, this, &ShDrawMenu::circleCenterRadiusActionClicked);
	connect(this->circleCenterDiameterAction, &QAction::triggered, this, &ShDrawMenu::circleCenterDiameterActionClicked);
	connect(this->circleTwoPointAction, &QAction::triggered, this, &ShDrawMenu::circleTwoPointActionClicked);
	connect(this->circleThreePointAction, &QAction::triggered, this, &ShDrawMenu::circleThreePointActionClicked);

}

void ShDrawMenu::createArcMenu() {

	this->arcMenu = new QMenu(shGetLanValue_ui("Draw/Arc"), this);
	this->addMenu(this->arcMenu);

	this->arcThreePointAction = new QAction(ShIcon(":/Image/Draw/Arc/3Point.png"), 
		shGetLanValue_ui("Draw/Arc,ThreePoints"), this->arcMenu);
	this->arcMenu->addAction(this->arcThreePointAction);


	this->arcMenu->addSeparator();

	this->arcStartCenterEndAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-Center-End.png"), 
		shGetLanValue_ui("Draw/Arc,Start,Center,End"), this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterEndAction);

	this->arcStartCenterAngleAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-Center-Angle.png"), 
		shGetLanValue_ui("Draw/Arc,Start,Center,Angle"), this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterAngleAction);

	this->arcStartCenterLengthAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-Center-Length.png"), 
		shGetLanValue_ui("Draw/Arc,Start,Center,Length"), this->arcMenu);
	this->arcMenu->addAction(this->arcStartCenterLengthAction);


	this->arcMenu->addSeparator();

	this->arcStartEndAngleAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-End-Angle.png"), 
		shGetLanValue_ui("Draw/Arc,Start,End,Angle"), this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndAngleAction);

	this->arcStartEndDirectionAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-End-Direction.png"), 
		shGetLanValue_ui("Draw/Arc,Start,End,Direction"), this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndDirectionAction);

	this->arcStartEndRadiusAction = new QAction(ShIcon(":/Image/Draw/Arc/Start-End-Radius.png"), 
		shGetLanValue_ui("Draw/Arc,Start,End,Radius"), this->arcMenu);
	this->arcMenu->addAction(this->arcStartEndRadiusAction);


	this->arcMenu->addSeparator();

	this->arcCenterStartEndAction = new QAction(ShIcon(":/Image/Draw/Arc/Center-Start-End.png"), 
		shGetLanValue_ui("Draw/Arc,Center,Start,End"), this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartEndAction);

	this->arcCenterStartAngleAction = new QAction(ShIcon(":/Image/Draw/Arc/Center-Start-Angle.png"), 
		shGetLanValue_ui("Draw/Arc,Center,Start,Angle"), this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartAngleAction);

	this->arcCenterStartLengthAction = new QAction(ShIcon(":/Image/Draw/Arc/Center-Start-Length.png"), 
		shGetLanValue_ui("Draw/Arc,Center,Start,Length"), this->arcMenu);
	this->arcMenu->addAction(this->arcCenterStartLengthAction);

	connect(this->arcThreePointAction, &QAction::triggered, this, &ShDrawMenu::arcThreePointActionClicked);

	connect(this->arcStartCenterEndAction, &QAction::triggered, this, &ShDrawMenu::arcStartCenterEndActionClicked);
	connect(this->arcStartCenterAngleAction, &QAction::triggered, this, &ShDrawMenu::arcStartCenterAngleActionClicked);
	connect(this->arcStartCenterLengthAction, &QAction::triggered, this, &ShDrawMenu::arcStartCenterLengthActionClicked);

	connect(this->arcStartEndAngleAction, &QAction::triggered, this, &ShDrawMenu::arcStartEndAngleActionClicked);
	connect(this->arcStartEndDirectionAction, &QAction::triggered, this, &ShDrawMenu::arcStartEndDirectionActionClicked);
	connect(this->arcStartEndRadiusAction, &QAction::triggered, this, &ShDrawMenu::arcStartEndRadiusActionClicked);

	connect(this->arcCenterStartEndAction, &QAction::triggered, this, &ShDrawMenu::arcCenterStartEndActionClicked);
	connect(this->arcCenterStartAngleAction, &QAction::triggered, this, &ShDrawMenu::arcCenterStartAngleActionClicked);
	connect(this->arcCenterStartLengthAction, &QAction::triggered, this, &ShDrawMenu::arcCenterStartLengthActionClicked);
}

void ShDrawMenu::lineActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawLine);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::circleCenterRadiusActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleCenterRadius);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::circleCenterDiameterActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleCenterDiameter);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::circleTwoPointActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleTwoPoint);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::circleThreePointActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawCircleThreePoint);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcThreePointActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcThreePoint);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcStartCenterEndActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartCenterEnd);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcStartCenterAngleActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartCenterAngle);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcStartCenterLengthActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartCenterLength);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcStartEndAngleActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartEndAngle);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcStartEndDirectionActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartEndDirection);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcStartEndRadiusActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcStartEndRadius);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcCenterStartEndActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcCenterStartEnd);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcCenterStartAngleActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcCenterStartAngle);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDrawMenu::arcCenterStartLengthActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawArcCenterStartLength);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

/////////////////////////////////////////////////////////////////////////

ShModifyMenu::ShModifyMenu(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractMenu(title, chain, parent) {

	this->eraseAction = new QAction(ShIcon(":/Image/Modify/Erase.png"), shGetLanValue_ui("Modify/Erase"), this);
	this->addAction(this->eraseAction);

	this->copyAction = new QAction(ShIcon(":/Image/Modify/Copy.png"), shGetLanValue_ui("Modify/Copy"), this);
	this->addAction(this->copyAction);

	this->mirrorAction = new QAction(ShIcon(":/Image/Modify/Mirror.png"), shGetLanValue_ui("Modify/Mirror"), this);
	this->addAction(this->mirrorAction);

	this->addSeparator();

	this->moveAction = new QAction(ShIcon(":/Image/Modify/Move.png"), shGetLanValue_ui("Modify/Move"), this);
	this->addAction(this->moveAction);

	this->rotateAction = new QAction(ShIcon(":/Image/Modify/Rotate.png"), shGetLanValue_ui("Modify/Rotate"), this);
	this->addAction(this->rotateAction);

	this->scaleAction = new QAction(ShIcon(":/Image/Modify/Scale.png"), shGetLanValue_ui("Modify/Scale"), this);
	this->addAction(this->scaleAction);

	this->stretchAction = new QAction(ShIcon(":/Image/Modify/Stretch.png"), shGetLanValue_ui("Modify/Stretch"), this);
	this->addAction(this->stretchAction);

	this->addSeparator();

	this->trimAction = new QAction(ShIcon(":/Image/Modify/Trim.png"), shGetLanValue_ui("Modify/Trim"), this);
	this->addAction(this->trimAction);

	this->extendAction = new QAction(ShIcon(":/Image/Modify/Extend.png"), shGetLanValue_ui("Modify/Extend"), this);
	this->addAction(this->extendAction);

	connect(this->moveAction, &QAction::triggered, this, &ShModifyMenu::moveActionClicked);
	connect(this->copyAction, &QAction::triggered, this, &ShModifyMenu::copyActionClicked);
	connect(this->mirrorAction, &QAction::triggered, this, &ShModifyMenu::mirrorActionClicked);
	connect(this->rotateAction, &QAction::triggered, this, &ShModifyMenu::rotateActionClicked);
	connect(this->eraseAction, &QAction::triggered, this, &ShModifyMenu::eraseActionClicked);
	connect(this->extendAction, &QAction::triggered, this, &ShModifyMenu::extendActionClicked);
	connect(this->trimAction, &QAction::triggered, this, &ShModifyMenu::trimActionClicked);
	connect(this->stretchAction, &QAction::triggered, this, &ShModifyMenu::stretchActionClicked);

}

ShModifyMenu::~ShModifyMenu() {

}

void ShModifyMenu::moveActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyMove);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyMenu::copyActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyCopy);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyMenu::mirrorActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyMirror);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyMenu::rotateActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyRotate);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyMenu::eraseActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyErase);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyMenu::extendActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyExtend);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyMenu::trimActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyTrim);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShModifyMenu::stretchActionClicked() {

	ShChangeModifyAfterCancelingCurrentStrategy strategy(ActionType::ActionModifyStretch);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

////////////////////////////////////////////////////////////////

ShWindowMenu::ShWindowMenu(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractMenu(title, chain, parent) {

	this->tabbedViewAction = new QAction(shGetLanValue_ui("Window/TabbedView"), this);
	this->addAction(this->tabbedViewAction);

	this->subWindowViewAction = new QAction(shGetLanValue_ui("Window/SubWindowView"), this);
	this->addAction(this->subWindowViewAction);

	this->cascadeAction = new QAction(shGetLanValue_ui("Window/Cascade"), this);
	this->addAction(this->cascadeAction);

	this->tileAction = new QAction(shGetLanValue_ui("Window/Tile"), this);
	this->addAction(this->tileAction);

	connect(this->tabbedViewAction, &QAction::triggered, this, &ShWindowMenu::tabbedViewActionClicked);
	connect(this->subWindowViewAction, &QAction::triggered, this, &ShWindowMenu::subWindowViewActionClicked);
	connect(this->cascadeAction, &QAction::triggered, this, &ShWindowMenu::cascadeActionClicked);
	connect(this->tileAction, &QAction::triggered, this, &ShWindowMenu::tileActionClicked);

}

ShWindowMenu::~ShWindowMenu() {

}

void ShWindowMenu::tabbedViewActionClicked() {

	ShRequestChangeViewMode request(ShRequestChangeViewMode::ViewMode::TabbedView);
	this->request(&request);
}

void ShWindowMenu::subWindowViewActionClicked() {

	ShRequestChangeViewMode request(ShRequestChangeViewMode::ViewMode::SubWindowView);
	this->request(&request);
}

void ShWindowMenu::cascadeActionClicked() {

	ShRequestChangeViewMode request(ShRequestChangeViewMode::ViewMode::Cascade);
	this->request(&request);
}

void ShWindowMenu::tileActionClicked() {

	ShRequestChangeViewMode request(ShRequestChangeViewMode::ViewMode::Tile);
	this->request(&request);
}


/////////////////////////////////////////////////////////////////////

ShDimMenu::ShDimMenu(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractMenu(title, chain, parent) {

	this->dimLinearAcion = new QAction(ShIcon(":/Image/Dimension/DimLinear.png"), shGetLanValue_ui("Dim/Linear"), this);
	this->addAction(this->dimLinearAcion);

	this->dimAlignedAction = new QAction(ShIcon(":/Image/Dimension/DimAligned.png"), shGetLanValue_ui("Dim/Aligned"), this);
	this->addAction(this->dimAlignedAction);

	this->dimAngularAction = new QAction(ShIcon(":/Image/Dimension/DimAngular.png"), shGetLanValue_ui("Dim/Angular"), this);
	this->addAction(this->dimAngularAction);

	this->dimRadiusAction = new QAction(ShIcon(":/Image/Dimension/DimRadius.png"), shGetLanValue_ui("Dim/Radius"), this);
	this->addAction(this->dimRadiusAction);

	this->dimDiameterAction = new QAction(ShIcon(":/Image/Dimension/DimDiameter.png"), shGetLanValue_ui("Dim/Diameter"), this);
	this->addAction(this->dimDiameterAction);

	this->dimArcLengthAction = new QAction(ShIcon(":/Image/Dimension/DimArcLength.png"), shGetLanValue_ui("Dim/ArcLength"), this);
	this->addAction(this->dimArcLengthAction);

	connect(this->dimLinearAcion, &QAction::triggered, this, &ShDimMenu::dimLinearActionClicked);
}

ShDimMenu::~ShDimMenu() {

}

void ShDimMenu::dimLinearActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimLinear);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimMenu::dimAlignedActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimAligned);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimMenu::dimAngularActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimAngular);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimMenu::dimRadiusActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimRadius);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimMenu::dimDiameterActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimDiameter);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}

void ShDimMenu::dimArcLengthActionClicked() {

	ShChangeActionAfterCancelingCurrentStrategy strategy(ActionType::ActionDrawDimArcLength);
	ShRequestChangeActionHandler request(&strategy);
	this->request(&request);
}