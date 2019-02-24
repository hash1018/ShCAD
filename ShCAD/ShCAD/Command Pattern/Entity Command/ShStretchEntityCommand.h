

#ifndef _SHSTRETCHENTITYCOMMAND_H
#define _SHSTRETCHENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include <qlinkedlist.h>
#include "ShVariable.h"
#include "ShPoint.h"
class ShGraphicView;
class ShEntity;
class ShStretchEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	QLinkedList<ShEntity*> entities;
	QLinkedList<HitPoint> hitPoints;
	ShPoint3d previous;
	ShPoint3d current;

	//store clone entities before taking execution.
	QLinkedList<ShEntity*> originalEntities;

public:
	ShStretchEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& entities,
		const QLinkedList<HitPoint>& hitPoints, const ShPoint3d& previous, const ShPoint3d& current);

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShStretchEntityCommand();



};

#endif //_SHSTRETCHENTITYCOMMAND_H