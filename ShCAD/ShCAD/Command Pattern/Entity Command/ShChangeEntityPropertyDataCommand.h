

#ifndef _SHCHANGEENTITYPROPERTYDATACOMMAND_H
#define _SHCHANGEENTITYPROPERTYDATACOMMAND_H

#include "Command Pattern\ShCommand.h"
#include "ShPropertyData.h"
#include <qlinkedlist.h>

class ShGraphicView;
class ShCompositeEntityMemento;
class ShEntity;
class ShChangeEntityPropertyDataCommand : public ShCommand {
public:
	enum ChangedType {
		Color=0,
		LineStyle=1,
	};

private:
	ChangedType type;
	ShGraphicView *view;
	ShColor color;
	ShLineStyle lineStyle;
	QLinkedList<ShEntity*> selectedEntities;
	QLinkedList<ShColor> previousColors;
	QLinkedList<ShLineStyle> previousLineStyles;
public:
	ShChangeEntityPropertyDataCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& selectedEntities,
		const QLinkedList<ShColor>& previousColors, const ShColor& color);

	ShChangeEntityPropertyDataCommand(ShGraphicView *view, const QLinkedList<ShEntity*>& selectedEntities,
		const QLinkedList<ShLineStyle>& previousLineStyles, const ShLineStyle& lineStyle);

	virtual void Execute();
	virtual void UnExecute();

protected:
	~ShChangeEntityPropertyDataCommand();



};

#endif //_SHCHANGEENTITYPROPERTYDATACOMMAND_H