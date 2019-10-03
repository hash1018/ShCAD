
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

#ifndef _SHAXIS_H
#define _SHAXIS_H

#include "Data\ShPoint3d.h"

class QPainter;
class ShCADWidget;
class ShAxis {

private:
	ShPoint3d center;

public:
	ShAxis();
	ShAxis(double centerX, double centerY);
	~ShAxis();
	ShAxis(const ShAxis& other);
	ShAxis& operator=(const ShAxis& other);

	void draw(QPainter *painter, ShCADWidget *widget);

	inline ShPoint3d getCenter() const { return this->center; }
	void setCenter(const ShPoint3d& center) { this->center = center; }

};

#endif //_SHAXIS_H