

#ifndef _SHSTRETCHENTITYCOMMAND_H
#define _SHSTRETCHENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include <qlist.h>
class ShGraphicView;
class ShEntity;
class ShStretchEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	QList<ShEntity*> stretchedEntites;
	QList<ShEntity*> originalEntities;

	bool mustDeallocateOriginal;
	bool mustDeallocateStretched;
	
public:
	ShStretchEntityCommand(ShGraphicView *view, const QList<ShEntity*>& originalEntities, const QList<ShEntity*>& stretchedEntites);

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShStretchEntityCommand();

};

#endif //_SHSTRETCHENTITYCOMMAND_H