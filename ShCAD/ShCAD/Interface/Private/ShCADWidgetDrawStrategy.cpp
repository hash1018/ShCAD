
#include "ShCADWidgetDrawStrategy.h"
#include "ShCADWidgetDrawStrategyFactory.h"
#include "Interface\ShCADWidget.h"
#include <qpainter.h>
#include <qdebug.h>
#include "ActionHandler\ShActionHandlerProxy.h"
#include "Entity\Private\ShDrawer.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Interface\Private\ShAxis.h"
#include "Entity\Composite\ShPreview.h"

ShCADWidgetDrawStrategy::ShCADWidgetDrawStrategy(ShCADWidget *widget, QPainter *painter)
	:widget(widget), painter(painter), strategy(nullptr) {

}

ShCADWidgetDrawStrategy::ShCADWidgetDrawStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	: widget(widget), painter(painter) {

	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);

}


ShCADWidgetDrawStrategy::~ShCADWidgetDrawStrategy() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShCADWidgetDrawStrategy::draw() {

	if (this->strategy != nullptr)
		this->strategy->draw();
}


ShDrawAllStrategy::ShDrawAllStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter, drawType) {


}

ShDrawAllStrategy::~ShDrawAllStrategy() {

}

void ShDrawAllStrategy::draw() {

	ShDrawerUnSelectedEntity unselected(this->widget);
	ShDrawerSelectedEntity *selected = ShDrawerSelectedEntityFactory::create(this->widget, 
		this->widget->getActionHandlerProxy()->getTypeIgonoringTemp());

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->widget->getEntityTable().turnOnLayerBegin();
		itr != this->widget->getEntityTable().turnOnLayerEnd();
		++itr) {
	
		if ((*itr)->isSelected() == false)
			(*itr)->accept(&unselected);
		else
			(*itr)->accept(selected);
	}

	if (selected != nullptr)
		delete selected;


	this->widget->getAxis().draw(this->painter, this->widget);

	if (this->strategy != nullptr)
		this->strategy->draw();
}


//////////////////////////////////////////////////////////////


ShDrawCaptureImageStrategy::ShDrawCaptureImageStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter, drawType) {


}

ShDrawCaptureImageStrategy::~ShDrawCaptureImageStrategy() {

}

void ShDrawCaptureImageStrategy::draw() {

	if (this->painter->isActive() == false)
		this->painter->begin(this->widget);

	this->painter->drawImage(0, 0, this->widget->getCapturedImage(), 0, 0, 0, 0);
	this->painter->end();

	if (this->strategy != nullptr)
		this->strategy->draw();
}



///////////////////////////////////////////////////////////////




ShDrawPreviewEntitiesStrategy::ShDrawPreviewEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter, drawType) {


}

ShDrawPreviewEntitiesStrategy::	~ShDrawPreviewEntitiesStrategy() {

}

void ShDrawPreviewEntitiesStrategy::draw() {

	ShDrawerUnSelectedEntity drawer(this->widget);
	drawer.visit(&(this->widget->getRubberBand()));

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->widget->getPreview().begin(); itr != this->widget->getPreview().end(); ++itr)
		(*itr)->accept(&drawer);
	

	if (this->strategy != nullptr)
		this->strategy->draw();
}



//////////////////////////////////////////////////////////////



ShDrawAddedEntitiesStrategy::ShDrawAddedEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter, drawType) {


}

ShDrawAddedEntitiesStrategy::~ShDrawAddedEntitiesStrategy() {

}

void ShDrawAddedEntitiesStrategy::draw() {

	ShDrawerUnSelectedEntity drawer(this->widget);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->widget->getEntityTable().justAddedEntityBegin();
		itr != this->widget->getEntityTable().justAddedEntityEnd();
		++itr) {
	
		(*itr)->accept(&drawer);
	}

	if (this->strategy != nullptr)
		this->strategy->draw();
}



//////////////////////////////////////////////////////////////



ShDrawSelectedEntitiesStrategy::ShDrawSelectedEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter, drawType) {


}

ShDrawSelectedEntitiesStrategy::~ShDrawSelectedEntitiesStrategy() {

}

void ShDrawSelectedEntitiesStrategy::draw() {

	ShDrawerEraseBackGround drawer(this->widget);

	ShDrawerSelectedEntity *selected = ShDrawerSelectedEntityFactory::create(this->widget, 
		this->widget->getActionHandlerProxy()->getTypeIgonoringTemp());

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->widget->getSelectedEntities()->getJustSelectedBegin();
		itr != this->widget->getSelectedEntities()->getJustSelectedEnd();
		++itr) {

		(*itr)->accept(&drawer);
		(*itr)->accept(selected);
	}

	if (selected != nullptr)
		delete selected;

	if (this->strategy != nullptr)
		this->strategy->draw();
}



//////////////////////////////////////////////////////////////



ShDrawJustTurnOnLayerStrategy::ShDrawJustTurnOnLayerStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter, drawType) {


}

ShDrawJustTurnOnLayerStrategy::~ShDrawJustTurnOnLayerStrategy() {

}

void ShDrawJustTurnOnLayerStrategy::draw() {

	ShDrawerUnSelectedEntity unSelected(this->widget);
	ShDrawerSelectedEntity *selected = ShDrawerSelectedEntityFactory::create(this->widget, 
		this->widget->getActionHandlerProxy()->getTypeIgonoringTemp());
	
	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->widget->getEntityTable().justTurnOnLayerBegin();
	itr != this->widget->getEntityTable().justTurnOnLayerEnd();
	++itr) {

		if ((*itr)->isSelected() == false)
			(*itr)->accept(&unSelected);
		else
			(*itr)->accept(selected);

	}

	if (selected != nullptr)
		delete selected;
	
	if (this->strategy != nullptr)
		this->strategy->draw();
}



///////////////////////////////////////////////////////////////


ShDrawActionHandlerStrategy::ShDrawActionHandlerStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter, drawType) {


}

ShDrawActionHandlerStrategy::~ShDrawActionHandlerStrategy() {

}

void ShDrawActionHandlerStrategy::draw() {

	this->widget->getActionHandlerProxy()->draw(this->painter);

	if (this->strategy != nullptr)
		this->strategy->draw();
}

	