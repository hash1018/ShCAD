
#ifndef _SHDRAGSELECTACTION_H
#define _SHDRAGSELECTACTION_H

#include "ShTemporaryAction.h"

class ShDragSelectAction : public ShTemporaryAction {

public:
	enum Mode {
		SelectMode,
		UnSelectMode,
	};

	enum SelectMethod {
		AllPart,
		OnePart,
	};

protected:
	double firstX;
	double firstY;
	double secondX;
	double secondY;
	Mode mode;
	
public:
	ShDragSelectAction(ShCADWidget *widget, double firstX, double firstY, Mode mode = SelectMode);
	~ShDragSelectAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QCursor getCursorShape();
	virtual void draw(QPainter *painter);

	virtual QString getHeadTitle();

protected:
	void getDragRectPoint(const ShPoint3d &first, const ShPoint3d &second, ShPoint3d &topLeft, ShPoint3d &bottomRight, SelectMethod &selectMethod);
	void searchEntities(const ShPoint3d &first, const ShPoint3d &second, QLinkedList<ShEntity*> &searchedList);
	int getAlreadySelectedCount(const QLinkedList<ShEntity*> &searchedList);
};

class ShModifyDragSelectAction : public ShDragSelectAction {

public:
	ShModifyDragSelectAction(ShCADWidget *widget, double firstX, double firstY, Mode mode = SelectMode);
	~ShModifyDragSelectAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	
	virtual QString getHeadTitle();
};




#endif //_SHDRAGSELECTACTION_H