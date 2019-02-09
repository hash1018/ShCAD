
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

 
/*   

**   This class is the class for determining whether a mouse cursor hovers or intersects  
**   specific area of a given entity object (such as line, circle, or arc) drawn on the graphicView.


*/


#ifndef _SHHITTESTER_H
#define _SHHITTESTER_H

#include "ShVisitor.h"
#include "ShVariable.h"
class ShHitTester : public ShVisitor {

private:
	double x;
	double y;
	double zoomRate;
	HitPoint &hitPoint;
	double tolerance;

public:
	ShHitTester(double x, double y, double zoomRate, HitPoint &hitPoint, double tolerance = 6.0);
	~ShHitTester();

	void Visit(ShLine *line);
	void Visit(ShCircle *circle);
	void Visit(ShArc *arc);

};



#endif //_SHHITTESTER_H