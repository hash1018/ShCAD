

#ifndef _SHCADWIDGETDRAWSTRATEGY_H
#define _SHCADWIDGETDRAWSTRATEGY_H

#include "Base\ShVariable.h"

class ShCADWidget;
class QPainter;

class ShCADWidgetDrawStrategy {

protected:
	ShCADWidget *widget;
	QPainter *painter;
	ShCADWidgetDrawStrategy *strategy;

public:
	ShCADWidgetDrawStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShCADWidgetDrawStrategy();

	virtual void draw();

protected:
	ShCADWidgetDrawStrategy(ShCADWidget *widget, QPainter *painater);

};


class ShDrawAllStrategy : public ShCADWidgetDrawStrategy {
	friend class ShCADWidgetDrawStrategyFactory;


private:
	ShDrawAllStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShDrawAllStrategy();

	virtual void draw();
};

//////////////////////////////////////////////////////////////

class ShDrawCaptureImageStrategy : public ShCADWidgetDrawStrategy {
	friend class ShCADWidgetDrawStrategyFactory;

private:
	ShDrawCaptureImageStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShDrawCaptureImageStrategy();

	virtual void draw();

};

///////////////////////////////////////////////////////////////


class ShDrawPreviewEntitiesStrategy : public ShCADWidgetDrawStrategy {
	friend class ShCADWidgetDrawStrategyFactory;

private:
	ShDrawPreviewEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShDrawPreviewEntitiesStrategy();

	virtual void draw();

};

//////////////////////////////////////////////////////////////


class ShDrawAddedEntitiesStrategy : public ShCADWidgetDrawStrategy {
	friend class ShCADWidgetDrawStrategyFactory;

private:
	ShDrawAddedEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShDrawAddedEntitiesStrategy();

	virtual void draw();

};

//////////////////////////////////////////////////////////////


class ShDrawSelectedEntitiesStrategy : public ShCADWidgetDrawStrategy {
	friend class ShCADWidgetDrawStrategyFactory;

private:
	ShDrawSelectedEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShDrawSelectedEntitiesStrategy();

	virtual void draw();

};

//////////////////////////////////////////////////////////////


class ShDrawJustTurnOnLayerStrategy : public ShCADWidgetDrawStrategy {
	friend class ShCADWidgetDrawStrategyFactory;

private:
	ShDrawJustTurnOnLayerStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShDrawJustTurnOnLayerStrategy();

	virtual void draw();

};

///////////////////////////////////////////////////////////////


class ShDrawActionHandlerStrategy : public ShCADWidgetDrawStrategy {
	friend class ShCADWidgetDrawStrategyFactory;

private:
	ShDrawActionHandlerStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType);
	~ShDrawActionHandlerStrategy();

	virtual void draw();


};


#endif //SHCADWIDGETDRAWSTRATEGY_H