
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

#include "ShAxis.h"

ShAxis::ShAxis()
	:center(0,0,0) {

}

ShAxis::ShAxis(double centerX, double centerY)
	: center(centerX, centerY) {

}

ShAxis::ShAxis(const ShAxis& other)
	: center(other.center) {


}

ShAxis& ShAxis::operator=(const ShAxis& other) {

	this->center = other.center;

	return *this;
}

ShAxis::~ShAxis() {

}

void ShAxis::SetCenter(const ShPoint3d& center) {

	this->center = center;
}

#include "qpainter.h"
#include "Interface\ShGraphicView.h"
#include "ShMath.h"
void ShAxis::Draw(QPainter *painter, ShGraphicView *view) {

	if (painter->isActive() == false)
		painter->begin(view);

	double hPos = view->GetHPos();
	double vPos = view->GetVPos();
	double zoomRate = view->GetZoomRate();

	QPen pen = painter->pen();
	painter->setPen(QColor(255, 255, 255));


	painter->drawLine(Math::ToInt(this->center.x*zoomRate - hPos), Math::ToInt(this->center.y*zoomRate - vPos),
		Math::ToInt(this->center.x*zoomRate + 100 - hPos), Math::ToInt(this->center.y*zoomRate - vPos));

	painter->drawLine(Math::ToInt(this->center.x*zoomRate - hPos), Math::ToInt(this->center.y*zoomRate - vPos),
		Math::ToInt(this->center.x*zoomRate - hPos), Math::ToInt(this->center.y*zoomRate - 100 - vPos));


	painter->drawText(this->center.x*zoomRate + 90 - hPos, this->center.y*zoomRate + 15 - vPos, "X");
	painter->drawText(this->center.x*zoomRate - 15 - hPos, this->center.y*zoomRate - 90 - vPos, "Y");
	painter->drawText(this->center.x*zoomRate - 15 - hPos, this->center.y*zoomRate + 15 - vPos, "O");
	
	
	
	painter->setPen(pen);

	painter->end();
}