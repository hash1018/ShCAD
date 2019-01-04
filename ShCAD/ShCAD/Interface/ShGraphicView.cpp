

#include "ShGraphicView.h"

ShGraphicView::ShGraphicView(QWidget *parent)
	:QOpenGLWidget(parent){

	this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	this->setMouseTracking(true);

}

ShGraphicView::~ShGraphicView() {

}

