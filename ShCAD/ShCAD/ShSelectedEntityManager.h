

#ifndef _SHSELECTEDENTITYMANAGER_H
#define _SHSELECTEDENTITYMANAGER_H

#include <qlinkedlist.h>
class ShEntity;
class ShSelectedEntityManager {

private:
	QLinkedList<ShEntity*> list;

public:
	ShSelectedEntityManager();
	~ShSelectedEntityManager();
	ShSelectedEntityManager(const ShSelectedEntityManager& other);
	ShSelectedEntityManager& operator=(const ShSelectedEntityManager& other);

	//returns false if entity is already selected.
	bool Push(ShEntity *entity);

	//returns false if entity is not already selected.
	bool Pop(ShEntity *entity);
	
	void UnSelectAll();

	int GetSize();

	ShEntity* GetRecentSelected();

};

#endif //_SHSELECTEDENTITYMANAGER_H