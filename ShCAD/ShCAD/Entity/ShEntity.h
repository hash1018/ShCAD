


#ifndef _SHENTITY_H
#define _SHENTITY_H

/*Base class for all objects having a graphical representation.*/

#include "Memento Pattern\ShMemento.h"

typedef struct ShEntityData {


}ShEntityData;

class ShEntityMemento;
class ShVisitor;
class ShEntity {

protected:
	bool isSelected;

public:
	ShEntity();
	virtual ~ShEntity() = 0;
	ShEntity(const ShEntity& other);
	ShEntity& operator=(const ShEntity& other);

	virtual ShEntity* Clone() = 0;
	virtual void Accept(ShVisitor *shVisitor) = 0;

	virtual ShEntityMemento* CreateMemento() { return 0; }
	virtual void SetMemento(const ShEntityMemento* memento) {}

	bool IsSelected() const;

	friend class ShSelectedEntityManager;
protected:
	void Select();
	void UnSelect();
};

inline bool ShEntity::IsSelected() const {

	return this->isSelected;
}



#endif //_SHENTITY_H
