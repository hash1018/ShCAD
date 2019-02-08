
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
#include "ShPropertyData.h"
class ShEntity;
class ShEntityTable;
class ShLayer;
class ShGraphicView;
class ShSelectedEntityManager {

private:
	QLinkedList<ShEntity*> list;
	QLinkedList<ShEntity*> justSelectedEntityList;
	QLinkedList<ShEntity*> justUnSelectedEntityList;

	ShPropertyData propertyDataForCombo;
	ShPropertyData layerPropertyDataForCombo;
	ShPropertyData blockPropertyDataForCombo;
	ShLayer *layerForCombo;
	bool isAllSameColor;
	bool isAllSameLineStyle;
	bool isAllSameLayer;

	ShGraphicView *view;

public:
	
	ShSelectedEntityManager();
	~ShSelectedEntityManager();
	ShSelectedEntityManager(const ShSelectedEntityManager& other);
	ShSelectedEntityManager& operator=(const ShSelectedEntityManager& other);
	
	void SetGraphicView(ShGraphicView *view);

	//returns false if entity is already selected.
	bool Push(ShEntity *entity);

	//returns false if entity is not already selected.
	bool Pop(ShEntity *entity);
	
	void SelectAll(ShEntityTable *entityTable);
	void UnSelectAll();

	int GetSize();

	inline QLinkedList<ShEntity*>::iterator GetJustSelectedBegin() { return this->justSelectedEntityList.begin(); }
	inline QLinkedList<ShEntity*>::iterator GetJustSelectedEnd() { return this->justSelectedEntityList.end(); }
	inline QLinkedList<ShEntity*>::iterator GetJustUnSelectedBegin() { return this->justUnSelectedEntityList.begin(); }
	inline QLinkedList<ShEntity*>::iterator GetJustUnSelectedEnd() { return this->justUnSelectedEntityList.end(); }
	inline QLinkedList<ShEntity*>::iterator Begin() { return this->list.begin(); }
	inline QLinkedList<ShEntity*>::iterator End() { return this->list.end(); }


	inline ShPropertyData GetDataForCombo() const { return this->propertyDataForCombo; }
	inline ShLayer* GetLayerForCombo() { return this->layerForCombo; }
	inline bool IsAllSameColor() const { return this->isAllSameColor; }
	inline bool IsAllSameLineStyle() const { return this->isAllSameLineStyle; }
	inline bool IsAllSameLayer() const { return this->isAllSameLayer; }


private:
	void RemoveAll(QLinkedList<ShEntity*> &list);

	void UpdateDataForCombo();
};

#endif //_SHSELECTEDENTITYMANAGER_H