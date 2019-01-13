

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

void ShAxis::SetCenter(const ShVector& center) {

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