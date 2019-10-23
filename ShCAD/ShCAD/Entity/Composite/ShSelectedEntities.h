
#ifndef _SHSELECTEDENTITIES_H
#define _SHSELECTEDENTITIES_H

#include "ShComposite.h"

class ShCADWidget;
class ShDim;
class ShSelectedEntities : public ShComposite {

private:
	QLinkedList<ShEntity*> justSelectedList;
	ShCADWidget *widget;

	QLinkedList<ShDim*> dimSelectedList;
public:
	ShSelectedEntities();
	~ShSelectedEntities();

	virtual bool add(ShEntity *entity);
	virtual bool add(const QLinkedList<ShEntity*> &list);

	virtual bool deleteEntity(ShEntity *entity);
	virtual bool remove(ShEntity *entity);
	virtual bool remove(const QLinkedList<ShEntity*> &list);
	
	void unSelectAll();

	virtual ShSelectedEntities* clone();
	virtual void accept(ShVisitor *visitor);

	void registerCADWidget(ShCADWidget *widget) { this->widget = widget; }

public:
	inline QLinkedList<ShEntity*>::iterator getJustSelectedBegin() { return this->justSelectedList.begin(); }
	inline QLinkedList<ShEntity*>::iterator getJustSelectedEnd() { return this->justSelectedList.end(); }
	inline const QLinkedList<ShEntity*>& getSelectedList() const { return this->list; }
	inline int getSelectedDimensionCount() const { return this->dimSelectedList.count(); }
	inline const QLinkedList<ShDim*>& getDimSelectedList() const { return this->dimSelectedList; }
	
private:
	void selectedEntityCountChanged();
	
};

#endif //_SHSELECTEDENTITIES_H