

#ifndef _SHMIRRORENTITYCOMMAND_H
#define _SHMIRRORENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include <qlinkedlist.h>
#include "ShPoint.h"
class ShGraphicView;
class ShEntity;
class ShMirrorEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	QLinkedList<ShEntity*> list;
	ShPoint3d center;
	double angle;

public:
	ShMirrorEntityCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& list, const ShPoint3d& center, double angle);


	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShMirrorEntityCommand();
};


#endif //_SHMIRRORENTITYCOMMAND_H