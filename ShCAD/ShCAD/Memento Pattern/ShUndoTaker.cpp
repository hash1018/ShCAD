
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

#include "ShUndoTaker.h"
#include "Command Pattern\ShCommand.h"
//delete 할때 전방선언 된 상태에서 지우니깐 클래스를 못찾아가는건가?

ShUndoTaker::ShUndoTaker() {

}

ShUndoTaker::~ShUndoTaker() {
	
	while (!this->IsEmpty())
		this->Pop()->Destroy();
	
}

void ShUndoTaker::Push(ShCommand *command) {

	if (this->stack.size() > 30) {
		this->stack[0]->Destroy();
		this->stack.pop_front();
	}

	this->stack.push(command);
}

ShCommand* ShUndoTaker::Pop() {

	if (this->stack.isEmpty()) {
		qDebug("Stack is empty");
		return 0;
	}

	return this->stack.pop();
}

bool ShUndoTaker::IsEmpty() {

	return this->stack.isEmpty();
}

void ShUndoTaker::DeleteAll() {

	while (!this->IsEmpty())
		this->Pop()->Destroy();

}