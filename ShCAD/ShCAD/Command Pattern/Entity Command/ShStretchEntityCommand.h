

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
	QLinkedList<VertexPoint> vertexPoints;
	ShPoint3d base;
	ShPoint3d current;
	

	//store clone entities before taking execution.
	QLinkedList<ShEntity*> originalEntities;

public:
	ShStretchEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& entities,
		const QLinkedList<VertexPoint>& vertexPoints, const ShPoint3d& base, const ShPoint3d& current);

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShStretchEntityCommand();

private:
	void DeleteOriginalAll();
	void StoreOriginal();

};

#endif //_SHSTRETCHENTITYCOMMAND_H