

#ifndef _SHCHANGEENTITYLAYER_H
#define _SHCHANGEENTITYLAYER_H

#include "Command Pattern\ShCommand.h"
#include <qlinkedlist.h>

class ShGraphicView;
class ShLayer;
class ShEntity;
class ShChangeEntityLayerCommand : public ShCommand {

private:
	ShGraphicView *view;
	ShLayer *changedLayer;
	QLinkedList<ShLayer*> previousLayers;
	QLinkedList<ShEntity*> selectedEntities;
	
public:
	ShChangeEntityLayerCommand(ShGraphicView *view, QLinkedList<ShEntity*>& selectedEntities,
		QLinkedList<ShLayer*>& previousLayers, ShLayer *changedLayer);
	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangeEntityLayerCommand();

};

#endif //_SHCHANGEENTITYLAYER_H