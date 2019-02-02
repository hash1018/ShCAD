
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

#include "ShMemento.h"
ShMemento::ShMemento(){

	

}

ShMemento::~ShMemento() {
	
}

//////////////////////////////////////////////////////////////////////

ShEntityMemento::ShEntityMemento()
	:entity(0), mustDeallocateEntity(false) {

}

//#include "Entity\ShEntity.h"
ShEntityMemento::~ShEntityMemento() {
	//qDebug("~ShEntityMemento");
	if (this->entity != 0 && this->mustDeallocateEntity == true)
		delete this->entity;

	if (this->propertyData != 0)
		delete this->propertyData;
}

////////////////////////////////////////////////////////////////////////

ShLineMemento::ShLineMemento() {
	
	
}

ShLineMemento::~ShLineMemento() {
	
	if (this->data != 0)
		delete this->data;

}

////////////////////////////////////////////////////////////////////////

ShMoveViewMemento::ShMoveViewMemento() {

}

ShMoveViewMemento::~ShMoveViewMemento() {

}

////////////////////////////////////////////////////////////////////////


ShCompositeEntityMemento::ShCompositeEntityMemento() {

}

ShCompositeEntityMemento::~ShCompositeEntityMemento() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();
	
}

////////////////////////////////////////////////////////////////////

ShLayerMemento::ShLayerMemento()
	:layer(0), mustDeallocateLayer(false) {

}


ShLayerMemento::~ShLayerMemento() {
	

	if (this->data != 0)
		delete this->data;
	
	if (this->layer != 0 && this->mustDeallocateLayer == true)
		delete this->layer;
	
}