

#ifndef _SHMODIFYCOPYACTION_H
#define _SHMODIFYCOPYACTION_H

#include "ShModifyAction.h"

class ShAddEntityTransaction;
class ShModifyCopyAction : public ShModifyAction {

private:
	ShAddEntityTransaction *transaction;

public:
	ShModifyCopyAction(ShCADWidget *widget);
	~ShModifyCopyAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();


	virtual void invalidate(ShPoint3d point);

	virtual void finishSelectingEntities();

private:
	void addCopiedEntities(const QLinkedList<ShEntity*> &list);
};

#endif //_SHMODIFYCOPYACTION_H