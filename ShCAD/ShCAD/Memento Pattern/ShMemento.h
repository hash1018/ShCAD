
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


#ifndef _SHMEMENTO_H
#define _SHMEMENTO_H

#include "ShVariable.h"
#include <qlinkedlist.h>

class ShEntity;
class ShMemento {

public:
	ShMemento();
	virtual ~ShMemento() = 0;
	
};

class ShEntityMemento : public ShMemento {

	friend class ShAddEntityCommand;
	friend class ShDeleteEntityCommand;

public:
	virtual ~ShEntityMemento() = 0;

protected:
	ShEntityMemento();

protected:
	ShEntity *entity;

	// if true  do not deallocate in the destructor.
	bool mustDeallocateEntity;
};


class ShLine;
class ShLineData;
class ShLineMemento : public ShEntityMemento {
	
	friend class ShLine;

public:
	~ShLineMemento();
	
private:
	ShLineMemento();
	
private:
	ShLineData *data;

};


class ShPanMoveAction;
class ShMoveViewMemento : public ShMemento {
	
	friend class ShPanMoveAction;
	friend class ShMoveViewCommand;

public:
	~ShMoveViewMemento();
private:
	ShMoveViewMemento();

private:
	double ex;
	double ey;
	double zoomRate;
	int dx;
	int dy;

};

class ShDeletedEntitiesMemento : public ShMemento {

	//friend class ShActionHandler;
	friend class ShCadAction;
	friend class ShDeleteEntityCommand;

private:
	ShDeletedEntitiesMemento();
public:
	~ShDeletedEntitiesMemento();

private:
	QLinkedList<ShEntityMemento*> list;

};

class ShLayerData;
class ShLayerMemento : public ShMemento {
	friend class ShLayer;
	friend class ShLayerToolBar;
	friend class ShLayerColumn;
	friend class ShLayerDialog;
	friend class ShChangeLayerDataCommand;
	
public:
	~ShLayerMemento();
private:
	ShLayerMemento();

private:
	ShLayerData *data;
};


#endif //_SHMEMENTO_H