

#include "ShCADWidget.h"
#include "ShGraphicView.h"
ShCADWidget::ShCADWidget(ShGraphicView *graphicView, QWidget *parent)
	:QWidget(parent) {

	this->graphicView = graphicView;
	this->graphicView->setParent(this);
	this->graphicView->setGeometry(this->rect());
	this->graphicView->show();
	
}

ShCADWidget::~ShCADWidget() {


}

#include <QResizeEvent>
void ShCADWidget::resizeEvent(QResizeEvent *event) {
	
	QWidget::resizeEvent(event);

	qDebug("ShCADWidget (New Size) - Width: %d Height: %d",
		event->size().width(), event->size().height());


	this->graphicView->setGeometry(this->rect());

}
