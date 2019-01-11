
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

#include "ShRedoTaker.h"
#include "Memento Pattern\ShMemento.h"
ShRedoTaker::ShRedoTaker() {

}

ShRedoTaker::~ShRedoTaker() {

	while (!this->IsEmpty())
		delete this->Pop();

}

void ShRedoTaker::Push(ShMemento *memento) {

	if (this->stack.size() > 30) {
		delete this->stack[0];
		this->stack.pop_front();
	}

	this->stack.push(memento);
}

ShMemento* ShRedoTaker::Pop() {

	if (this->stack.isEmpty()) {
		qDebug("Stack is empty");
		return 0;
	}

	return this->stack.pop();
}

bool ShRedoTaker::IsEmpty() {

	return this->stack.isEmpty();
}

void ShRedoTaker::DeleteAll() {

	while (!this->IsEmpty())
		delete this->Pop();

}