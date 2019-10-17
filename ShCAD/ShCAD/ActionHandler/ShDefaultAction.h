

#ifndef _SHDEFAULTACTION_H
#define _SHDEFAULTACTION_H

#include "ShActionHandler.h"

class ShSubDefaultAction;
class ShDefaultAction : public ShActionHandler {

	friend class ShSubDefaultAction;

private:
	ShSubDefaultAction *subDefaultAction;

public:
	ShDefaultAction(ShCADWidget *widget);
	~ShDefaultAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();
	
	void changeSubAction(ShSubDefaultAction *subDefaultAction);

private:
	void escPressed();

};

///////////////////////////////////////////////////////////////////////////////////

class ShSubDefaultAction {

protected:
	ShDefaultAction *defaultAction;
	ShCADWidget *widget;

public:
	ShSubDefaultAction(ShDefaultAction *defaultAction, ShCADWidget *widget);
	virtual ~ShSubDefaultAction() = 0;

	virtual void mouseLeftPressEvent(ShActionData &data) = 0;
	virtual void mouseMoveEvent(ShActionData &data) = 0;

protected:
	void setLastBasePoint(const ShPoint3d &point) { this->defaultAction->setLastBasePoint(point); }
};

class ShSubDefaultAction_Default : public ShSubDefaultAction {

public:
	ShSubDefaultAction_Default(ShDefaultAction *defaultAction, ShCADWidget *widget);
	~ShSubDefaultAction_Default();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

};

class ShSubDefaultAction_MouseIsInShapeVertex : public ShSubDefaultAction {

private:
	ShPoint3d vertexPoint;

public:
	ShSubDefaultAction_MouseIsInShapeVertex(ShDefaultAction *defaultAction, ShCADWidget *widget, const ShPoint3d &vertexPoint);
	~ShSubDefaultAction_MouseIsInShapeVertex();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

private:
	void drawVertex();
};

class ShSubDefaultAction_MouseIsInAxisOrigin : public ShSubDefaultAction {

public:
	ShSubDefaultAction_MouseIsInAxisOrigin(ShDefaultAction *defaultAction, ShCADWidget *widget);
	~ShSubDefaultAction_MouseIsInAxisOrigin();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

private:
	void drawAxisOrigin();

};
#endif //_SHDEFAULTACTION_H