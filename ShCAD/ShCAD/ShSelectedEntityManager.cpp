
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

#include "ShSelectedEntityManager.h"
#include "Entity\ShEntity.h"
#include "Entity\Composite\ShEntityTable.h"

ShSelectedEntityManager::Iterator::Iterator() {


}

ShSelectedEntityManager::Iterator::Iterator(const ShSelectedEntityManager::Iterator& other) {

	this->itr = other.itr;
	this->begin = other.begin;
	this->end = other.end;

}

ShSelectedEntityManager::Iterator& ShSelectedEntityManager::Iterator::operator=(const ShSelectedEntityManager::Iterator& other) {

	this->itr = other.itr;
	this->begin = other.begin;
	this->end = other.end;
	return *this;
}

ShSelectedEntityManager::Iterator::~Iterator() {

}

ShEntity* ShSelectedEntityManager::Iterator::Current() {

	return (*this->itr);
}

bool ShSelectedEntityManager::Iterator::IsEnd() {

	if ((*this->itr) == (*this->end))
		return true;

	return false;
}

bool ShSelectedEntityManager::Iterator::IsBegin() {

	if ((*this->itr) == (*this->begin))
		return true;

	return false;
}

void ShSelectedEntityManager::Iterator::Previous() {

	--this->itr;
}

void ShSelectedEntityManager::Iterator::Next() {

	++this->itr;
}


ShSelectedEntityManager::ShSelectedEntityManager() {

}

ShSelectedEntityManager::~ShSelectedEntityManager() {

}

ShSelectedEntityManager::ShSelectedEntityManager(const ShSelectedEntityManager& other)
	:list(other.list) {

}

ShSelectedEntityManager& ShSelectedEntityManager::operator=(const ShSelectedEntityManager& other) {

	this->list = other.list;

	return *this;
}

bool ShSelectedEntityManager::Push(ShEntity *entity) {

	if (entity->IsSelected() == true)
		return false;

	entity->Select();
	this->list.append(entity);


	////
	//this->justUnSelectedEntityList.empty();
	this->RemoveAll(this->justUnSelectedEntityList);

	//this->justSelectedEntityList.empty();
	this->RemoveAll(this->justSelectedEntityList);

	this->justSelectedEntityList.append(entity);
	////

	return true;
}

bool ShSelectedEntityManager::Pop(ShEntity *entity) {

	if (entity->IsSelected() == false)
		return false;

	entity->UnSelect();
	this->list.removeOne(entity);

	////
	//this->justSelectedEntityList.empty();
	this->RemoveAll(this->justSelectedEntityList);

	//this->justUnSelectedEntityList.empty();
	this->RemoveAll(this->justUnSelectedEntityList);

	this->justUnSelectedEntityList.append(entity);
	////

	return true;
}

void ShSelectedEntityManager::SelectAll(ShEntityTable *entityTable) {

	
	this->RemoveAll(this->justSelectedEntityList);

	//ShComposite::Iterator itr = composite->Begin();

	//while (!itr.IsEnd()) {
	
	//	if (itr.Current()->IsSelected() == false) {
			
	//		itr.Current()->Select();
	//		this->list.append(itr.Current());

	//		this->justSelectedEntityList.append(itr.Current());
	//	}

	//	itr.Next();
	//}


	QLinkedList<ShEntity*>::iterator itr;

	for (itr = entityTable->TurnOnLayerBegin(); itr != entityTable->TurnOnLayerEnd(); ++itr) {
	
		if ((*itr)->IsSelected() == false) {
		
			(*itr)->Select();
			this->list.append((*itr));
			this->justSelectedEntityList.append((*itr));
		}
	}

	
	this->RemoveAll(this->justUnSelectedEntityList);
}

void ShSelectedEntityManager::UnSelectAll() {

	//this->justUnSelectedEntityList.empty();
	this->RemoveAll(this->justUnSelectedEntityList);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {
		(*itr)->UnSelect();
		this->justUnSelectedEntityList.append((*itr));
	}

	//this->list.empty();
	this->RemoveAll(this->list);


	//this->justSelectedEntityList.empty();
	this->RemoveAll(this->justSelectedEntityList);


}


int ShSelectedEntityManager::GetSize() {

	return this->list.size();
}


ShSelectedEntityManager::Iterator ShSelectedEntityManager::GetJustSelectedBegin() {

	ShSelectedEntityManager::Iterator itr;

	itr.begin = this->justSelectedEntityList.begin();
	itr.end = this->justSelectedEntityList.end();
	itr.itr = this->justSelectedEntityList.begin();

	return itr;
}


ShSelectedEntityManager::Iterator ShSelectedEntityManager::GetJustSelectedEnd() {

	ShSelectedEntityManager::Iterator itr;

	itr.begin = this->justSelectedEntityList.begin();
	itr.end = this->justSelectedEntityList.end();
	itr.itr = this->justSelectedEntityList.end();

	return itr;
}

ShSelectedEntityManager::Iterator ShSelectedEntityManager::GetJustUnSelectedBegin() {

	ShSelectedEntityManager::Iterator itr;

	itr.begin = this->justUnSelectedEntityList.begin();
	itr.end = this->justUnSelectedEntityList.end();
	itr.itr = this->justUnSelectedEntityList.begin();

	return itr;
}

ShSelectedEntityManager::Iterator ShSelectedEntityManager::GetJustUnSelectedEnd() {

	ShSelectedEntityManager::Iterator itr;

	itr.begin = this->justUnSelectedEntityList.begin();
	itr.end = this->justUnSelectedEntityList.end();
	itr.itr = this->justUnSelectedEntityList.end();

	return itr;
}

void ShSelectedEntityManager::RemoveAll(QLinkedList<ShEntity*> &list) {

	while (!list.isEmpty())
		list.removeFirst();
	
}