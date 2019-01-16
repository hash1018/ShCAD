

#include "ShDrawer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Interface\ShGraphicView.h"
ShDrawer::ShDrawer(ShGraphicView *view, DrawType drawType)
	:view(view), drawType(drawType) {

}

ShDrawer::~ShDrawer() {

	
}

void ShDrawer::Visit(ShLine *shLine) {

	if (shLine->IsSelected() == true) {
		ShSelectedEntityDrawer selectedDrawer(this->view, this->drawType);
		shLine->Accept(&selectedDrawer);
		return;
	}

	ShLineData data=shLine->GetData();

	GLPoint start, end;

	this->ConvertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	this->ConvertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	GLColor color(1.0f, 1.0f, 1.0f); //only temporary color.

	this->DrawLine(start, end, color);

}

void ShDrawer::Visit(ShCircle *shCircle) {


}

void ShDrawer::Visit(ShArc *shArc) {


}

void ShDrawer::Visit(ShRubberBand *shRubberBand) {
	
	ShLineData data = shRubberBand->GetData();

	GLPoint start, end;

	this->ConvertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	this->ConvertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	GLColor color(1.0f, 1.0f, 1.0f); 

	this->DrawLine(start, end, color);
	

}

void ShDrawer::ConvertDeviceToOpenGL(int x, int y, double  &ox, double  &oy) {

	int w = this->view->height();
	int h = this->view->width();
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

void ShDrawer::DrawLine(const GLPoint& start, const GLPoint& end, const GLColor& color) {
	
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();
}


ShSelectedEntityDrawer::ShSelectedEntityDrawer(ShGraphicView *view, DrawType drawType)
	:ShDrawer(view, drawType) {

}

ShSelectedEntityDrawer::~ShSelectedEntityDrawer() {

}

void ShSelectedEntityDrawer::Visit(ShLine *shLine) {
	//qDebug("ShSelectedEntityDrawer->Visit");
	
	ShLineData data = shLine->GetData();

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

}

void ShSelectedEntityDrawer::Visit(ShCircle *shCircle) {

}

void ShSelectedEntityDrawer::Visit(ShArc *shArc) {

}