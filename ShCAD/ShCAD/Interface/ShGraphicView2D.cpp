

#include "ShGraphicView2D.h"


ShGraphicView2D::ShGraphicView2D(QWidget *parent)
	:ShGraphicView(parent) {


}

ShGraphicView2D::~ShGraphicView2D() {


}



void ShGraphicView2D::initializeGL() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


void ShGraphicView2D::paintGL() {

}


void ShGraphicView2D::mousePressEvent(QMouseEvent *event) {

	qDebug("asdasd");
}

void ShGraphicView2D::mouseMoveEvent(QMouseEvent *event) {

	qDebug("MouseMove");
}