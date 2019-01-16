

#ifndef _SHSELECTEDENTITYMANAGER_H
#define _SHSELECTEDENTITYMANAGER_H

#include <qlinkedlist.h>

class ShEntity;
class ShComposite;
class ShSelectedEntityManager {

private:
	QLinkedList<ShEntity*> list;
	QLinkedList<ShEntity*> justSelectedEntityList;
	QLinkedList<ShEntity*> justUnSelectedEntityList;

public:
	class Iterator {
		friend class ShSelectedEntityManager;
	private:
		QLinkedList<ShEntity*>::iterator itr;
		QLinkedList<ShEntity*>::iterator begin;
		QLinkedList<ShEntity*>::iterator end;

	public:
		Iterator();
		Iterator(const Iterator& other);
		Iterator& operator=(const Iterator& other);
		~Iterator();

		ShEntity* Current();
		bool IsEnd();
		bool IsBegin();
		void Previous();
		void Next();
	};

	ShSelectedEntityManager();
	~ShSelectedEntityManager();
	ShSelectedEntityManager(const ShSelectedEntityManager& other);
	ShSelectedEntityManager& operator=(const ShSelectedEntityManager& other);

	//returns false if entity is already selected.
	bool Push(ShEntity *entity);

	//returns false if entity is not already selected.
	bool Pop(ShEntity *entity);
	
	void SelectAll(ShComposite *composite);
	void UnSelectAll();

	int GetSize();

	ShSelectedEntityManager::Iterator GetJustSelectedBegin();
	ShSelectedEntityManager::Iterator GetJustSelectedEnd();

	ShSelectedEntityManager::Iterator GetJustUnSelectedBegin();
	ShSelectedEntityManager::Iterator GetJustUnSelectedEnd();


private:
	void RemoveAll(QLinkedList<ShEntity*> &list);
};

#endif //_SHSELECTEDENTITYMANAGER_H