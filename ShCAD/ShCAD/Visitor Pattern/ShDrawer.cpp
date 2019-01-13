

#include "ShDrawer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Interface\ShGraphicView.h"
ShDrawer::ShDrawer(ShGraphicView *view)
	:view(view) {

}

ShDrawer::~ShDrawer() {


}

void ShDrawer::Visit(ShLine *shLine) {

	ShLineData data=shLine->GetData();

	double x, y;
	this->ConvertEntityToOpenGL(data.start.x, data.start.y, x, y);

	glColor3f(255, 255, 255);

	glBegin(GL_LINES);
	glVertex2f(x, y);

	this->ConvertEntityToOpenGL(data.end.x, data.end.y, x, y);
	glVertex2f(x, y);
	glEnd();

}

void ShDrawer::Visit(ShCircle *shCircle) {


}

void ShDrawer::Visit(ShArc *shArc) {


}

void ShDrawer::Visit(ShRubberBand *shRubberBand) {
	
	ShLineData data = shRubberBand->GetData();

	double x, y;
	this->ConvertEntityToOpenGL(data.start.x, data.start.y, x, y);

	glColor3f(255, 255, 255);

	glBegin(GL_LINES);
	glVertex2f(x, y);

	this->ConvertEntityToOpenGL(data.end.x, data.end.y, x, y);
	glVertex2f(x, y);
	glEnd();

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