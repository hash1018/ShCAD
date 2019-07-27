

#ifndef _SHDISPOSABLESNAPACTION_H
#define _SHDISPOSABLESNAPACTION_H

#include "ShDecoratorAction.h"

class ShDisposableSnapAction : public ShDecoratorAction {

public:
	ShDisposableSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child = nullptr);
	virtual ~ShDisposableSnapAction() = 0;

	virtual void keyPressEvent(ShActionData &data);
	virtual void draw(QPainter *painter);

	virtual void invalidate(ShPoint3d point);
};

class ShDisposableSnapAction_General : public ShDisposableSnapAction {

public:
	ShDisposableSnapAction_General(ShCADWidget *widget, ShActionHandler *actionHandler, ObjectSnap objectSnap, ShDecoratorAction *child = nullptr);
	~ShDisposableSnapAction_General();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

};

#endif //_SHDISPOSABLESNAPACTION_H