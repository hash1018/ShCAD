
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#ifndef _SHSELECTEDENTITYMANAGER_H
#define _SHSELECTEDENTITYMANAGER_H

#include <qlinkedlist.h>

class ShEntity;
class ShEntityTable;
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
	
	void SelectAll(ShEntityTable *entityTable);
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