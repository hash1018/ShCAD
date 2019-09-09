

#ifndef _SHDISPOSABLEEXTENSIONSNAPACTION_H
#define _SHDISPOSABLEEXTENSIONSNAPACTION_H


#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"

class ShDisposableExtensionSnapAction : public ShDisposableSnapAction {

public:
	ShDisposableExtensionSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableExtensionSnapAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);

};

#endif //_SHDISPOSABLEEXTENSIONSNAPACTION_H