
#include "ShPlotPreviewDialog.h"
#include "Manager\ShPlotManager.h"
#include <qprintpreviewwidget.h>
#include <qpainter.h>
#include "Interface\ShCADWidget.h"
#include "Manager\ShCADWidgetManager.h"


ShPlotPreviewDialog::ShPlotPreviewDialog(QWidget *parent)
	:QDialog(parent) {

	ShPlotManager *manager = ShPlotManager::getInstance();
	this->preview = new QPrintPreviewWidget(manager->getPrinter(), this);
	this->resize(1000, 800);
	this->preview->setGeometry(0, 0, this->width(), this->height());

	connect(this->preview, &QPrintPreviewWidget::paintRequested, this, &ShPlotPreviewDialog::printWidget);
}

ShPlotPreviewDialog::~ShPlotPreviewDialog() {

}

void ShPlotPreviewDialog::printWidget(QPrinter *printer) {

	QPainter painter(printer);
	ShPlotManager *plotManager = ShPlotManager::getInstance();
	ShCADWidget *widget = ShCADWidgetManager::getInstance()->getActivatedWidget();

	if (widget == nullptr)
		return;

	double xscale, yscale, scale;
	QRect drawRect;
	QRect windowRect;


	if (plotManager->getWhatToPlot() == WhatToPlot::PlotDisplay) {

		windowRect = widget->rect();
	}
	else {

		windowRect = this->convertWindowRect(plotManager->getWindowPrevX(), plotManager->getWindowPrevY(),
			plotManager->getWindowCurrentX(), plotManager->getWindowCurrentY());
	}

	xscale = printer->pageRect().width() / double(windowRect.width());
	yscale = printer->pageRect().height() / double(windowRect.height());
	scale = qMin(xscale, yscale);

	if (plotManager->getWhatToPlot() == WhatToPlot::PlotWindow)
		painter.translate(-double(windowRect.topLeft().x())*scale, -double(windowRect.topLeft().y())*scale);

	drawRect = QRect(0, 0, double(windowRect.width())*scale, double(windowRect.height())*scale);



	if (plotManager->isCenterThePlot() == true) {

		if (drawRect.width() >= drawRect.height()) {

			painter.translate(0, printer->pageRect().height() / 2);
			painter.translate(0, -((double)(windowRect.height())*scale) / 2);

			drawRect = QRect(0, printer->pageRect().height() / 2 - (double(drawRect.height())) / 2,
				drawRect.width(), drawRect.height());

		}
		else {


			painter.translate(printer->pageRect().width() / 2, 0);
			painter.translate(-((double)(windowRect.width())*scale) / 2, 0);

			drawRect = QRect(printer->pageRect().width() / 2 - (double(drawRect.width())) / 2, 0,
				drawRect.width(), drawRect.height());

		}
	}





	widget->plot(&painter, scale);

	painter.resetTransform();


	QRect rect(QPoint(0, 0), QPoint(drawRect.topRight()));
	painter.eraseRect(rect);
	rect = QRect(QPoint(drawRect.bottomLeft()), QPoint(printer->pageRect().width(), printer->pageRect().height()));
	painter.eraseRect(rect);
	rect = QRect(QPoint(0, 0), QPoint(drawRect.bottomLeft()));
	painter.eraseRect(rect);
	rect = QRect(QPoint(drawRect.topRight()), QPoint(printer->pageRect().width(), printer->pageRect().height()));
	painter.eraseRect(rect);


	QPoint point, point2;

	point = QPoint(-printer->paperRect().width(), -printer->paperRect().height());
	point2 = QPoint(printer->paperRect().width(), 0);
	painter.eraseRect(QRect(point, point2));

	point2 = QPoint(0, printer->paperRect().height());
	painter.eraseRect(QRect(point, point2));

	point = QPoint(-100, printer->pageRect().height());
	point2 = QPoint(printer->paperRect().bottomRight().x(), printer->paperRect().bottomRight().y());
	painter.eraseRect(QRect(point, point2));

	point = QPoint(printer->pageRect().width(), 0);
	painter.eraseRect(QRect(point, point2));


	painter.end();
}

QRect ShPlotPreviewDialog::convertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY) {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();
	int prevX, prevY, currentX, currentY;

	ShCADWidget *widget = manager->getActivatedWidget();

	widget->convertEntityToDevice(windowPrevX, windowPrevY, prevX, prevY);
	widget->convertEntityToDevice(windowCurrentX, windowCurrentY, currentX, currentY);

	int width = abs(prevX - currentX);
	int height = abs(prevY - currentY);
	int topLeftX, topLeftY;

	if (prevX > currentX) {
		topLeftX = currentX;
	}
	else {
		topLeftX = prevX;
	}

	if (prevY > currentY) {
		topLeftY = currentY;
	}
	else {
		topLeftY = prevY;
	}

	return QRect(QPoint(topLeftX, topLeftY), QPoint(topLeftX + width, topLeftY + height));
}