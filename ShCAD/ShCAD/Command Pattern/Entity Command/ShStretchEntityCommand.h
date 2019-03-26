

#ifndef _SHSTRETCHENTITYCOMMAND_H
#define _SHSTRETCHENTITYCOMMAND_H

#include "Command Pattern\ShCommand.h"
#include "ShVariable.h"
#include "ShPoint.h"
#include <qlist.h>
class ShGraphicView;
class ShEntity;
class ShStretchData;
class ShStretchEntityCommand : public ShCommand {

private:
	ShGraphicView *view;
	QList<ShEntity*> entitiesToStretch;
	QList<ShStretchData*> stretchDataList;
	ShPoint3d base;
	ShPoint3d current;

	QList<ShEntity*> originalEntities;
	
public:
	ShStretchEntityCommand(ShGraphicView *view, const QList<ShEntity*>& entitiesToStretch,
		const QList<ShStretchData*>& stretchDataList,
		const ShPoint3d& base, const ShPoint3d& current);

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShStretchEntityCommand();

private:
	void StoreOriginal();
	void DeleteOriginalAll();
};

#endif //_SHSTRETCHENTITYCOMMAND_H