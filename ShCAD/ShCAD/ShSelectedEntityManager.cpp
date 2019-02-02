
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
#include "Singleton Pattern\ShChangeManager.h"
#include "ShNotifyEvent.h"


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

void ShSelectedEntityManager::SetGraphicView(ShGraphicView *view) {

	this->view = view;
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

	this->UpdateDataForCombo();
	
	ShChangeManager *manager = ShChangeManager::GetInstance();

	ShSelectedEntityCountChangedEvent event(this->view, this->propertyDataForCombo,
		this->layerPropertyDataForCombo, this->blockPropertyDataForCombo, this->layerForCombo,
		this->isAllSameColor, this->isAllSameLineStyle, this->isAllSameLayer, this->list.size());

	manager->Notify(this, &event);

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

	this->UpdateDataForCombo();

	ShChangeManager *manager = ShChangeManager::GetInstance();

	ShSelectedEntityCountChangedEvent event(this->view, this->propertyDataForCombo,
		this->layerPropertyDataForCombo, this->blockPropertyDataForCombo, this->layerForCombo,
		this->isAllSameColor, this->isAllSameLineStyle, this->isAllSameLayer, this->list.size());

	manager->Notify(this, &event);

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

	this->UpdateDataForCombo();

	ShChangeManager *manager = ShChangeManager::GetInstance();

	ShSelectedEntityCountChangedEvent event(this->view, this->propertyDataForCombo,
		this->layerPropertyDataForCombo, this->blockPropertyDataForCombo, this->layerForCombo,
		this->isAllSameColor, this->isAllSameLineStyle, this->isAllSameLayer, this->list.size());

	manager->Notify(this, &event);

	
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

	this->UpdateDataForCombo();

	ShChangeManager *manager = ShChangeManager::GetInstance();

	ShSelectedEntityCountChangedEvent event(this->view, this->propertyDataForCombo,
		this->layerPropertyDataForCombo, this->blockPropertyDataForCombo, this->layerForCombo,
		this->isAllSameColor, this->isAllSameLineStyle, this->isAllSameLayer, this->list.size());

	manager->Notify(this, &event);
}


int ShSelectedEntityManager::GetSize() {

	return this->list.size();
}



void ShSelectedEntityManager::RemoveAll(QLinkedList<ShEntity*> &list) {

	while (!list.isEmpty())
		list.removeFirst();
	
}

void ShSelectedEntityManager::UpdateDataForCombo() {

	this->layerForCombo = 0;
	this->isAllSameColor = false;
	this->isAllSameLayer = false;
	this->isAllSameLineStyle = false;

	if (this->list.size() == 0)
		return;

	QLinkedList<ShEntity*>::iterator itr = this->list.begin();

	this->layerForCombo = (*itr)->GetLayer();
	this->propertyDataForCombo = (*itr)->GetPropertyData();
	this->layerPropertyDataForCombo = (*itr)->GetLayer()->GetPropertyData();

	this->isAllSameColor = true;
	this->isAllSameLayer = true;
	this->isAllSameLineStyle = true;

	++itr;

	while (itr != this->list.end()) {
	
		if (this->isAllSameColor == true)
			if ((*itr)->GetPropertyData().GetColor() != this->propertyDataForCombo.GetColor())
				this->isAllSameColor = false;
		
		if (this->isAllSameLineStyle == true)
			if ((*itr)->GetPropertyData().GetLineStyle() != this->propertyDataForCombo.GetLineStyle())
				this->isAllSameLineStyle = false;

		if (this->isAllSameLayer == true)
			if ((*itr)->GetLayer() != this->layerForCombo)
				this->isAllSameLayer = false;

	
		++itr;
	}




}