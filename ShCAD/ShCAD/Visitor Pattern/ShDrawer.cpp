

#include "ShDrawer.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Leaf\ShArc.h"
#include "Entity\Composite\ShPolyLine.h"
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

	if (circle->IsSelected() == true) {
		ShSelectedEntityDrawer selectedDrawer(this->view, this->drawType);
		selectedDrawer.Visit(circle);
		return;
	}

	ShCircleData data = circle->GetData();
	ShPropertyData propertyData = circle->GetPropertyData();


	GLColor color(propertyData.GetColor().GetRed() / 255., propertyData.GetColor().GetGreen() / 255.,
		propertyData.GetColor().GetBlue() / 255.);

	glLineStipple(1, propertyData.GetLineStyle().GetPattern());
	glEnable(GL_LINE_STIPPLE);
	this->DrawCircle(data.center, data.radius, color);
	glDisable(GL_LINE_STIPPLE);


}

void ShDrawer::Visit(ShArc *arc) {

	if (arc->IsSelected() == true) {
		ShSelectedEntityDrawer selectedDrawer(this->view, this->drawType);
		selectedDrawer.Visit(arc);
		return;
	}

	ShArcData data = arc->GetData();
	ShPropertyData propertyData = arc->GetPropertyData();

	GLColor color(propertyData.GetColor().GetRed() / 255., propertyData.GetColor().GetGreen() / 255.,
		propertyData.GetColor().GetBlue() / 255.);

	glLineStipple(1, propertyData.GetLineStyle().GetPattern());
	glEnable(GL_LINE_STIPPLE);

	if (Math::Compare(data.startAngle, data.endAngle) == 1) {
		this->DrawArc(data.center, data.radius, data.startAngle, 360, color);
		this->DrawArc(data.center, data.radius, 0, data.endAngle, color);
	}
	else 
		this->DrawArc(data.center, data.radius, data.startAngle, data.endAngle, color);
	

	glDisable(GL_LINE_STIPPLE);
}

void ShDrawer::Visit(ShRubberBand *rubberBand) {
	
	ShLineData data = rubberBand->GetData();

	GLPoint start, end;

	this->ConvertEntityToOpenGL(data.start.x, data.start.y, start.x, start.y);
	this->ConvertEntityToOpenGL(data.end.x, data.end.y, end.x, end.y);

	GLColor color(1.0, 153 / 255.0, 51 / 255.0);

	glLineStipple(1, 0x07FF);
	glEnable(GL_LINE_STIPPLE);
	this->DrawLine(start, end, color);
	glDisable(GL_LINE_STIPPLE);
	
}

void ShDrawer::Visit(ShPolyLine *polyLine) {

	QLinkedList<ShEntity*>::iterator itr;
	ShPolyLineChildDrawer visitor(this->view, this->drawType);
	for (itr = polyLine->Begin(); itr != polyLine->End(); ++itr)
		(*itr)->Accept(&visitor);

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
	ox = ((tempX - (double)w / 2.0)*(1.0 / ((double)w / 2.0)));
	oy = -((tempY - (double)h / 2.0)*(1.0 / ((double)h / 2.0)));

	
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

void ShDrawer::DrawFilledPolygon(GLPoint(*array), int length, const GLColor& color) {

	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POLYGON);

	for (int i = 0; i < length; i++) {
		glVertex2f(array[i].x, array[i].y);
	}

	glEnd();
}

void ShDrawer::DrawCircle(const ShPoint3d& center, double radius, const GLColor& color,int segments) {

	glColor3f(color.red, color.green, color.blue);

	double theta, x, y;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {
	
		theta = 2.0 * 3.1415926 * double(i) / double(segments);
		x = radius*cosf(theta);
		y = radius*sinf(theta);

		this->ConvertEntityToOpenGL(center.x + x, center.y + y, x, y);
		glVertex2f(x, y);
	}

	glEnd();
}

void ShDrawer::DrawArc(const ShPoint3d& center, double radius, double startAngle, double endAngle, const GLColor& color, int segments) {

	glColor3f(color.red, color.green, color.blue);

	double theta, x, y;
	
	glBegin(GL_LINE_STRIP);

	theta = 2.0 * 3.1415926 * double(startAngle) / double(segments);
	x = radius*cosf(theta);
	y = radius*sinf(theta);

	this->ConvertEntityToOpenGL(center.x + x, center.y + y, x, y);
	glVertex2f(x, y);

	for (int i = Math::ToInt(startAngle + 1); i <= Math::ToInt(endAngle - 1); i++) {
		
		theta = 2.0 * 3.1415926 * double(i) / double(segments);
		x = radius*cosf(theta);
		y = radius*sinf(theta);
		this->ConvertEntityToOpenGL(center.x + x, center.y + y, x, y);
		glVertex2f(x, y);
	}

	theta = 2.0 * 3.1415926 * double(endAngle) / double(segments);
	x = radius*cosf(theta);
	y = radius*sinf(theta);
	this->ConvertEntityToOpenGL(center.x + x, center.y + y, x, y);
	glVertex2f(x, y);

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

	if (this->view->EnabledDrawEntityVertex() == true) {

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


}

void ShSelectedEntityDrawer::Visit(ShCircle *circle) {

	ShCircleData data = circle->GetData();
	ShPropertyData propertyData = circle->GetPropertyData();

	GLColor color(propertyData.GetColor().GetRed() / 255., propertyData.GetColor().GetGreen() / 255.,
		propertyData.GetColor().GetBlue() / 255.);

	if (this->drawType == DrawType::DrawSelectedEntities) {
		//in this case, Draw entity with the background color of view
		//and Draw entity that represents it is selected.

		this->DrawCircle(data.center, data.radius, GLColor(0, 0, 0)); //third argument is the background color of view.
	}

	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	this->DrawCircle(data.center, data.radius, GLColor(153.f / 255, 153.f / 155, 1.f));
	glDisable(GL_LINE_STIPPLE);

	if (this->view->EnabledDrawEntityVertex() == true) {

		int centerX, centerY, centerPlusRadiusX, centerPlusRadiusY;
		this->ConvertEntityToDevice(data.center.x, data.center.y, centerX, centerY);
		this->ConvertEntityToDevice(data.center.x + data.radius, data.center.y, centerPlusRadiusX, centerPlusRadiusY);

		int deviceRadius = (int)Math::GetDistance(centerX, centerY, centerPlusRadiusX, centerPlusRadiusY);

		GLPoint topLeft, bottomRight;
		this->ConvertDeviceToOpenGL(centerX - 3, centerY - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(centerX + 3, centerY + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

		this->ConvertDeviceToOpenGL(centerX + deviceRadius - 3, centerY - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(centerX + deviceRadius + 3, centerY + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

		this->ConvertDeviceToOpenGL(centerX - deviceRadius - 3, centerY - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(centerX - deviceRadius + 3, centerY + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

		this->ConvertDeviceToOpenGL(centerX - 3, centerY + deviceRadius - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(centerX + 3, centerY + deviceRadius + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

		this->ConvertDeviceToOpenGL(centerX - 3, centerY - deviceRadius - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(centerX + 3, centerY - deviceRadius + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));
	}
}

void ShSelectedEntityDrawer::Visit(ShArc *arc) {

	ShArcData data = arc->GetData();
	ShPropertyData propertyData = arc->GetPropertyData();

	GLColor color(propertyData.GetColor().GetRed() / 255., propertyData.GetColor().GetGreen() / 255.,
		propertyData.GetColor().GetBlue() / 255.);

	if (this->drawType == DrawType::DrawSelectedEntities) {
		//in this case, Draw entity with the background color of view
		//and Draw entity that represents it is selected.

		if (Math::Compare(data.startAngle, data.endAngle) == 1) {
			this->DrawArc(data.center, data.radius, data.startAngle, 360, GLColor(0, 0, 0));
			this->DrawArc(data.center, data.radius, 0, data.endAngle, GLColor(0, 0, 0));
		}
		else
			this->DrawArc(data.center, data.radius, data.startAngle, data.endAngle, GLColor(0, 0, 0));//third argument is the background color of view.
	}


	glLineStipple(1, 0xF1F1);
	glEnable(GL_LINE_STIPPLE);

	if (Math::Compare(data.startAngle, data.endAngle) == 1) {
		this->DrawArc(data.center, data.radius, data.startAngle, 360, GLColor(153.f / 255, 153.f / 155, 1.f));
		this->DrawArc(data.center, data.radius, 0, data.endAngle, GLColor(153.f / 255, 153.f / 155, 1.f));
	}
	else
		this->DrawArc(data.center, data.radius, data.startAngle, data.endAngle, GLColor(153.f / 255, 153.f / 155, 1.f));
	
	glDisable(GL_LINE_STIPPLE);

	if (this->view->EnabledDrawEntityVertex() == true) {
		int x, y;
		GLPoint topLeft, bottomRight;

		this->ConvertEntityToDevice(data.center.x, data.center.y, x, y);
		this->ConvertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

		this->ConvertEntityToDevice(arc->GetStart().x, arc->GetStart().y, x, y);
		this->ConvertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

		this->ConvertEntityToDevice(arc->GetEnd().x, arc->GetEnd().y, x, y);
		this->ConvertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

		this->ConvertEntityToDevice(arc->GetMid().x, arc->GetMid().y, x, y);
		this->ConvertDeviceToOpenGL(x - 3, y - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(x + 3, y + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));

	}
	
}

void ShSelectedEntityDrawer::Visit(ShPolyLine *polyLine) {

	

}

////////////////////////////////////////////////////////////////////////////////////////


ShPolyLineChildDrawer::ShPolyLineChildDrawer(ShGraphicView *view, DrawType drawType)
	:ShDrawer(view, drawType) {

}

ShPolyLineChildDrawer::~ShPolyLineChildDrawer() {

}


void ShPolyLineChildDrawer::Visit(ShLine *line) {

	if (line->IsSelected() == true) {
		ShSelectedPolyLineChildDrawer selectedDrawer(this->view, this->drawType);
		selectedDrawer.Visit(line);
		return;
	}
	else {
		ShDrawer::Visit(line);
	}
}

void ShPolyLineChildDrawer::Visit(ShCircle *circle) {

}

void ShPolyLineChildDrawer::Visit(ShArc *arc) {

}

void ShPolyLineChildDrawer::Visit(ShPolyLine *polyLine) {


}


/////////////////////////////////////////////////////////////////

ShSelectedPolyLineChildDrawer::ShSelectedPolyLineChildDrawer(ShGraphicView *view, DrawType drawType)
	:ShDrawer(view, drawType) {

}

ShSelectedPolyLineChildDrawer::~ShSelectedPolyLineChildDrawer() {

}

void ShSelectedPolyLineChildDrawer::Visit(ShLine *line) {

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

	if (this->view->EnabledDrawEntityVertex() == true) {

		int startX, startY, midX, midY, endX, endY;
		this->ConvertEntityToDevice(data.start.x, data.start.y, startX, startY);
		this->ConvertEntityToDevice(data.end.x, data.end.y, endX, endY);
		this->ConvertEntityToDevice(line->GetMid().x, line->GetMid().y, midX, midY);

		GLPoint topLeft, bottomRight;
		this->ConvertDeviceToOpenGL(startX - 3, startY - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(startX + 3, startY + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));
		
		GLPoint center;
		this->ConvertDeviceToOpenGL(midX, midY, center.x, center.y);
		this->ConvertDeviceToOpenGL(midX - 4, midY - 4, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(midX + 4, midY + 4, bottomRight.x, bottomRight.y);
		

		GLPoint array[4] = { GLPoint(center.x,topLeft.y),GLPoint(topLeft.x,center.y),
		GLPoint(center.x,bottomRight.y),GLPoint(bottomRight.x,center.y) };
		this->DrawFilledPolygon(array, 4, GLColor(0.0, 1.0, 1.0));

		this->ConvertDeviceToOpenGL(endX - 3, endY - 3, topLeft.x, topLeft.y);
		this->ConvertDeviceToOpenGL(endX + 3, endY + 3, bottomRight.x, bottomRight.y);
		this->DrawFilledRect(topLeft, bottomRight, GLColor(0.0, 153.0 / 255, 1.0));
	}
}

void ShSelectedPolyLineChildDrawer::Visit(ShCircle *circle) {

}

void ShSelectedPolyLineChildDrawer::Visit(ShArc *arc) {

}

void ShSelectedPolyLineChildDrawer::Visit(ShPolyLine *polyLine) {


}