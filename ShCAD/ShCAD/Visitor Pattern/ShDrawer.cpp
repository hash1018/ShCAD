

#include "ShDrawer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShRubberBand.h"

ShDrawer::ShDrawer(int glWidth, int glHeight)
	:glWidth(glWidth), glHeight(glHeight) {

}

ShDrawer::~ShDrawer() {


}

void ShDrawer::Visit(ShLine *shLine) {

	ShLineData data=shLine->GetData();

	double x, y;
	this->ConvertDeviceXY2OpenglXY(data.start.x, data.start.y, x, y);

	glColor3f(255, 255, 255);

	glBegin(GL_LINES);
	glVertex2f(x, y);

	this->ConvertDeviceXY2OpenglXY(data.end.x, data.end.y, x, y);
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
	this->ConvertDeviceXY2OpenglXY(data.start.x, data.start.y, x, y);

	glColor3f(255, 255, 255);

	glBegin(GL_LINES);
	glVertex2f(x, y);

	this->ConvertDeviceXY2OpenglXY(data.end.x, data.end.y, x, y);
	glVertex2f(x, y);
	glEnd();

}

void ShDrawer::ConvertDeviceXY2OpenglXY(int x, int y, double  &ox, double  &oy) {

	int w = this->glWidth;
	int h = this->glHeight;
	ox = (double)((x - (double)w / 2.0)*(double)(1.0 / (double)(w / 2.0)));
	oy = -(double)((y - (double)h / 2.0)*(double)(1.0 / (double)(h / 2.0)));
}