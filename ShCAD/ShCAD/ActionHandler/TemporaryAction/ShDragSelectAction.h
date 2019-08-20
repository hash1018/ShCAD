
#ifndef _SHDRAGSELECTACTION_H
#define _SHDRAGSELECTACTION_H

#include "ShTemporaryAction.h"

class ShSelectionData {
	friend class ShDragSelectAction;

private:
	bool selectionMode;
	int searchedCount;
	int alreadySelectedCount;
	int removedCount;

public:
	ShSelectionData();
	~ShSelectionData();

	inline bool isSelectionMode() const { return this->selectionMode; }
	inline int getSearchedCount() const { return this->searchedCount; }
	inline int getAlreadySelectedCount() const { return this->alreadySelectedCount; }
	inline int getRemovedCount() const { return this->removedCount; }
};

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
	ShSelectionData *selectionData;


public:
	ShDragSelectAction(ShCADWidget *widget, double firstX, double firstY, Mode mode = SelectMode);
	~ShDragSelectAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QCursor getCursorShape();
	virtual void draw(QPainter *painter);

	virtual QString getHeadTitle();

public:
	void setSelectionData(ShSelectionData *selectionData) { this->selectionData = selectionData; }

protected:
	void getDragRectPoint(const ShPoint3d &first, const ShPoint3d &second, ShPoint3d &topLeft, ShPoint3d &bottomRight, SelectMethod &selectMethod);
	void searchEntities(const ShPoint3d &first, const ShPoint3d &second, QLinkedList<ShEntity*> &searchedList);
	int getAlreadySelectedCount(const QLinkedList<ShEntity*> &searchedList);
};

#endif //_SHDRAGSELECTACTION_H