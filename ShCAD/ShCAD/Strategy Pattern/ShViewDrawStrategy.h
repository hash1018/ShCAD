

#ifndef _SHVIEWDRAWSTRATEGY_H
#define _SHVIEWDRAWSTRATEGY_H

#include "ShVariable.h"
class ShGraphicView;
class QPainter;

class ShViewDrawStrategy {

protected:
	ShViewDrawStrategy *strategy;

public:
	ShViewDrawStrategy();
	ShViewDrawStrategy(ShGraphicView *view, QPainter* painter, DrawType drawType);
	~ShViewDrawStrategy();

	virtual void Draw();

};






class ShDrawAll : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawAll(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawAll();

	virtual void Draw();


};







class ShDrawCaptureImage : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawCaptureImage(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawCaptureImage();

	virtual void Draw();

};







class ShDrawPreviewEntities : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawPreviewEntities(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawPreviewEntities();

	virtual void Draw();

};








class ShDrawAddedEntities : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawAddedEntities(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawAddedEntities();

	virtual void Draw();

};







class ShDrawSelectedEntities : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawSelectedEntities(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawSelectedEntities();

	virtual void Draw();

};








class ShDrawJustUnSelectedEntities : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawJustUnSelectedEntities(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawJustUnSelectedEntities();

	virtual void Draw();

};








class ShDrawJustTurnOnLayer : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawJustTurnOnLayer(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawJustTurnOnLayer();

	virtual void Draw();

};







class ShDrawActionHandler : public ShViewDrawStrategy {
	friend class ShCreatorViewDrawFactory;
private:
	ShGraphicView *view;
	QPainter *painter;

private:
	ShDrawActionHandler(ShGraphicView *view, QPainter *painter, DrawType drawType);
	~ShDrawActionHandler();

	virtual void Draw();


};




#endif //SHVIEWDRAWSTRATEGY_H
