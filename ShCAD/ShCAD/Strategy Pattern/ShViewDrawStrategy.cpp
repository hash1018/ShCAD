

#include "ShViewDrawStrategy.h"
#include "FactoryMethod\ShCreatorViewDrawFactory.h"
#include "Visitor Pattern\ShDrawer.h"
#include "Interface\ShGraphicView.h"
#include <qpainter.h>

ShViewDrawStrategy::ShViewDrawStrategy()
	:strategy(0) {

}

ShViewDrawStrategy::ShViewDrawStrategy(ShGraphicView *view, QPainter *painter,DrawType drawType) {


	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);

}

ShViewDrawStrategy::~ShViewDrawStrategy() {

	if (this->strategy != 0)
		delete this->strategy;
}

void ShViewDrawStrategy::Draw() {

	if (this->strategy != 0)
		this->strategy->Draw();

}

///////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawAll::ShDrawAll(ShGraphicView *view, QPainter *painter, DrawType drawType)
	:view(view), painter(painter) {

	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);

}

ShDrawAll::~ShDrawAll() {

	
}


void ShDrawAll::Draw() {

	ShDrawer drawer(this->view, DrawType::DrawAll);

	this->view->axis.Draw(this->painter, this->view);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->view->entityTable.TurnOnLayerBegin(); itr != this->view->entityTable.TurnOnLayerEnd(); ++itr)
		(*itr)->Accept(&drawer);


	if (this->strategy != 0)
		this->strategy->Draw();

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawCaptureImage::ShDrawCaptureImage(ShGraphicView *view, QPainter *painter, DrawType drawType)
	:view(view), painter(painter) {

	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);
}

ShDrawCaptureImage::~ShDrawCaptureImage() {

	
}

void ShDrawCaptureImage::Draw() {

	if (this->painter->isActive() == false)
		this->painter->begin(this->view);

	this->painter->drawImage(0, 0, this->view->captureImage, 0, 0, 0, 0);
	this->painter->end();

	if (this->strategy != 0)
		this->strategy->Draw();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawPreviewEntities::ShDrawPreviewEntities(ShGraphicView *view, QPainter *painter, DrawType drawType)
	:view(view), painter(painter) {

	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);
}

ShDrawPreviewEntities::~ShDrawPreviewEntities() {

	
}

#include "Entity\Leaf\ShRubberBand.h"
void ShDrawPreviewEntities::Draw() {

	ShDrawer drawer(this->view, DrawType::DrawPreviewEntities);

	if (this->view->rubberBand != NULL) {
		this->view->rubberBand->Accept(&drawer);
	}

	QLinkedList<ShEntity*>::iterator itr;

	

	for (itr = this->view->preview.Begin(); itr != this->view->preview.End(); ++itr)
		(*itr)->Accept(&drawer);
	


	if (this->strategy != 0)
		this->strategy->Draw();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawAddedEntities::ShDrawAddedEntities(ShGraphicView *view, QPainter *painter, DrawType drawType)
	:view(view), painter(painter) {

	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);
}

ShDrawAddedEntities::~ShDrawAddedEntities() {

}


void ShDrawAddedEntities::Draw() {

	ShDrawer drawer(this->view, DrawType::DrawAddedEntities);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->view->entityTable.JustAddedEntitiesBegin(); itr != this->view->entityTable.JustAddedEntitiesEnd(); ++itr)
		(*itr)->Accept(&drawer);


	if (this->strategy != 0)
		this->strategy->Draw();

}

//////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawSelectedEntities::ShDrawSelectedEntities(ShGraphicView *view, QPainter *painter, DrawType drawType)
	:view(view), painter(painter) {

	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);

}
ShDrawSelectedEntities::~ShDrawSelectedEntities() {

}

void ShDrawSelectedEntities::Draw() {

	ShDrawer drawer(this->view, DrawType::DrawSelectedEntities);

	QLinkedList<ShEntity*>::iterator itr;
	
	for (itr = this->view->selectedEntityManager.GetJustSelectedBegin();
		itr != this->view->selectedEntityManager.GetJustSelectedEnd();
		++itr) {

		(*itr)->Accept(&drawer);
	}

	
	if (this->strategy != 0)
		this->strategy->Draw();

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShDrawJustTurnOnLayer::ShDrawJustTurnOnLayer(ShGraphicView *view, QPainter *painter, DrawType drawType)
	:view(view), painter(painter) {

	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);

}

ShDrawJustTurnOnLayer::~ShDrawJustTurnOnLayer() {

}


void ShDrawJustTurnOnLayer::Draw() {

	ShDrawer drawer(this->view, DrawType::DrawJustTurnOnLayer);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->view->entityTable.GetLayerTable()->GetJustTurnOnLayer()->Begin();
		itr != this->view->entityTable.GetLayerTable()->GetJustTurnOnLayer()->End();
		++itr) {

		(*itr)->Accept(&drawer);

	}

	if (this->strategy != 0)
		this->strategy->Draw();

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShDrawActionHandler::ShDrawActionHandler(ShGraphicView *view, QPainter *painter, DrawType drawType)
	:view(view), painter(painter) {

	this->strategy = ShCreatorViewDrawFactory::Create(view, painter, drawType);
}

ShDrawActionHandler::~ShDrawActionHandler() {

}

#include "ActionHandler\ShActionHandler.h"
void ShDrawActionHandler::Draw() {

	this->view->currentAction->Draw(this->painter);

	if (this->strategy != 0)
		this->strategy->Draw();

}