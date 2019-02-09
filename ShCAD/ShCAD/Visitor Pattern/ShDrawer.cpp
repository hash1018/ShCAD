

#include "ShDrawer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Interface\ShGraphicView.h"
#include "ShMath.h"
ShDrawer::ShDrawer(ShGraphicView *view, DrawType drawType)
	:view(view), drawType(drawType) {

}

ShDrawer::~ShDrawer() {

	
}

void ShDrawer::Visit(ShLine *line) {

	if (line->IsSelected() == true) {
		ShSelectedEntityDrawer selectedDrawer(this->view, this->drawType);
		selectedDrawer.Visit(line);
		return;
	}

	

	ShLineData data=line->GetData();
	ShPropertyData propertyData = line->GetPropertyData();
	GLPoint start, end;

	this->ConvertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	this->ConvertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);
	
	GLColor color(propertyData.GetColor().GetRed() / 255., propertyData.GetColor().GetGreen() / 255., 
		propertyData.GetColor().GetBlue() / 255.);

	glLineStipple(1, propertyData.GetLineStyle().GetPattern());
	glEnable(GL_LINE_STIPPLE);
	this->DrawLine(start, end, color);
	glDisable(GL_LINE_STIPPLE);

}

void ShDrawer::Visit(ShCircle *circle) {


}

void ShDrawer::Visit(ShArc *arc) {


}

void ShDrawer::Visit(ShRubberBand *rubberBand) {
	
	ShLineData data = rubberBand->GetData();

	GLPoint start, end;

	this->ConvertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	this->ConvertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	GLColor color(1.0f, 1.0f, 1.0f); 
	this->DrawLine(start, end, color);
	
}

void ShDrawer::ConvertDeviceToOpenGL(int x, int y, double  &ox, double  &oy) {

	int w = this->view->width();
	int h = this->view->height();
	ox = (double)((x - (double)w / 2.0)*(double)(1.0 / (double)(w / 2.0)));
	oy = -(double)((y - (double)h / 2.0)*(double)(1.0 / (double)(h / 2.0)));
}

void ShDrawer::ConvertEntityToOpenGL(double x, double y, double &ox, double &oy) {

	double zoomRate = this->view->GetZoomRate();
	double hPos = this->view->GetHPos();
	double vPos = this->view->GetVPos();
	double centerX = this->view->axis.GetCenter().x;
	double centerY = this->view->axis.GetCenter().y;


	double tempX = (x*zoomRate) - hPos + (centerX*zoomRate);
	double tempY = -1 * ((y*zoomRate) + vPos - (centerY*zoomRate));


	int w = this->view->width();
	int h = this->view->height();
	ox = (double)((tempX - (double)w / 2.0)*(double)(1.0 / (double)(w / 2.0)));
	oy = -(double)((tempY - (double)h / 2.0)*(double)(1.0 / (double)(h / 2.0)));
}


void ShDrawer::ConvertEntityToDevice(double x, double y, int &dx, int &dy) {

	double zoomRate = this->view->GetZoomRate();
	double hPos = this->view->GetHPos();
	double vPos = this->view->GetVPos();
	ShPoint3d center = this->view->axis.GetCenter();
	
	double tempX = ((x*zoomRate) - hPos + (center.x*zoomRate));
	double tempY = (-1 * ((y*zoomRate) + vPos - (center.y*zoomRate)));

	dx = Math::ToInt(tempX);
	dy = Math::ToInt(tempY);

}

void ShDrawer::DrawLine(const GLPoint& start, const GLPoint& end, const GLColor& color) {
	
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();
}

void ShDrawer::DrawFilledRect(const GLPoint& topLeft, const GLPoint& bottomRight, const GLColor& color) {

	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_QUADS);
	glVertex2f(topLeft.x, topLeft.y);
	glVertex2f(bottomRight.x, topLeft.y);
	glVertex2f(bottomRight.x, bottomRight.y);
	glVertex2f(topLeft.x, bottomRight.y);
	glEnd();
}


ShSelectedEntityDrawer::ShSelectedEntityDrawer(ShGraphicView *view, DrawType drawType)
	:ShDrawer(view, drawType) {

}

ShSelectedEntityDrawer::~ShSelectedEntityDrawer() {

}

void ShSelectedEntityDrawer::Visit(ShLine *line) {
	//qDebug("ShSelectedEntityDrawer->Visit");
	
	ShLineData data = line->GetData();

	GLPoint start, end;
	this->ConvertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	this->ConvertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);


	if (this->drawType == DrawType::DrawSelectedEntities) {
	//in this case, Draw entity with the background color of view
	//and Draw entity that represents it is selected.

		this->DrawLine(start, end, GLColor(0, 0, 0)); //third argument is the background color of view.
	}

	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	this->DrawLine(start, end, GLColor(153.f / 255, 153.f / 155, 1.f));
	glDisable(GL_LINE_STIPPLE);


	int startX, startY, midX, midY, endX, endY;
	this->ConvertEntityToDevice(data.start.x, data.start.y, startX, startY);
	this->ConvertEntityToDevice(data.end.x, data.end.y, endX, endY);
	this->ConvertEntityToDevice(line->GetMid().x, line->GetMid().y, midX, midY);

	GLPoint topLeft, bottomRight;
	this->ConvertDeviceToOpenGL(startX - 3, startY - 3, topLeft.x, topLeft.y);
	this->ConvertDeviceToOpenGL(startX + 3, startY + 3, bottomRight.x, bottomRight.y);
	this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	this->ConvertDeviceToOpenGL(midX - 3, midY - 3, topLeft.x, topLeft.y);
	this->ConvertDeviceToOpenGL(midX + 3, midY + 3, bottomRight.x, bottomRight.y);
	this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	this->ConvertDeviceToOpenGL(endX - 3, endY - 3, topLeft.x, topLeft.y);
	this->ConvertDeviceToOpenGL(endX + 3, endY + 3, bottomRight.x, bottomRight.y);
	this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));
	


}

void ShSelectedEntityDrawer::Visit(ShCircle *circle) {

}

void ShSelectedEntityDrawer::Visit(ShArc *arc) {

}

