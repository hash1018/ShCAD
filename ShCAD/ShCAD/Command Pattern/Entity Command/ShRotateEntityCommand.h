
#ifndef _SHROTATEENTITYCOMMAND_H
#define _SHROTATEENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include <qlinkedlist.h>
#include "ShPoint.h"
class ShGraphicView;
class ShEntity;
class ShRotateEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	QLinkedList<ShEntity*> list;
	ShPoint3d center;
	double angle;

public:
	ShRotateEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& list, const ShPoint3d& center, double angle);


	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShRotateEntityCommand();
};


#endif //_SHROTATEENTITYCOMMAND_H