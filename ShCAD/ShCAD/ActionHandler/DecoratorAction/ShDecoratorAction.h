
#ifndef _SHDECORATORACTION_H
#define _SHDECORATORACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShDecoratorAction : public ShActionHandler {

protected:
	ShActionHandler *actionHandler;
	ShDecoratorAction *parent;
	ShDecoratorAction *child;

public:
	ShDecoratorAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	virtual ~ShDecoratorAction() = 0;

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMidPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);
	virtual void mouseReleaseEvent(ShActionData &data);
	virtual void keyPressEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual ActionType getType();
	virtual QString getHeadTitle();

	virtual void invalidate(ShPoint3d point);

	void setParent(ShDecoratorAction *parent) { this->parent = parent; }
	inline ShDecoratorAction* getParent() const { return this->parent; }
	inline ShDecoratorAction* getChild() const { return this->child; }
};

#endif //_SHDECORATORACTION_H