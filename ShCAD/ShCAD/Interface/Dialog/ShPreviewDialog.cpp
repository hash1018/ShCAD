
#include "ShPreviewDialog.h"
#include "Singleton Pattern\ShPrinterManager.h"
#include <qprintpreviewwidget.h>
#include "Singleton Pattern\ShWidgetManager.h"
#include <qpainter.h>
#include "Interface\ShGraphicView.h"


ShPreviewDialog::ShPreviewDialog(QWidget *parent)
	:QDialog(parent) {

	ShPrinterManager *manager = ShPrinterManager::GetInstance();
	this->preview = new QPrintPreviewWidget(manager->Printer(), this);
	this->resize(1000, 800);
	this->preview->setGeometry(0, 0, this->width(), this->height());

	connect(this->preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(PrintWidgetTemp(QPrinter*)));
}

ShPreviewDialog::~ShPreviewDialog() {

}

void ShPreviewDialog::PrintWidget(QPrinter *printer) {


	QPainter painter(printer);
	ShPrinterManager *printerManager = ShPrinterManager::GetInstance();
	ShWidgetManager *manager = ShWidgetManager::GetInstance();
	double xscale, yscale, scale;
	QRect rect;

	if (printerManager->GetWhatToPlot() == WhatToPlot::PlotDisplay) {

		xscale = printer->pageRect().width() / double(manager->GetActivatedWidget()->width());
		yscale = printer->pageRect().height() / double(manager->GetActivatedWidget()->height());
		scale = qMin(xscale, yscale);

		int width = manager->GetActivatedWidget()->width();
		int height = manager->GetActivatedWidget()->height();

		if (width >= height) {
			rect = QRect(QPoint(printer->paperRect().topLeft().x(),
				double(height)*scale), QPoint(printer->pageRect().width(), printer->pageRect().height()));
		}
		else {
			rect = QRect(QPoint(double(width)*scale, printer->paperRect().topLeft().y()),
				QPoint(printer->pageRect().width(), printer->pageRect().height()));
		}

		if (printerManager->IsCenterThePlot() == true) {

			if (width >= height) {
				painter.translate(0, printer->paperRect().y() + printer->pageRect().height() / 2);
				painter.translate(0, -((double)(height)*scale) / 2);
			}
			else {
				painter.translate(printer->paperRect().x() + printer->pageRect().width() / 2, 0);
				painter.translate(-((double)(width)*scale) / 2, 0);
			}
		}

		manager->GetActivatedWidget()->Print(&painter, scale);
		painter.eraseRect(rect);

	}
	//Window
	else {
		QRect windowRect = this->ConvertWindowRect(printerManager->GetWindowPrevX(), printerManager->GetWindowPrevY(),
			printerManager->GetWindowCurrentX(), printerManager->GetWindowCurrentY());

		xscale = printer->pageRect().width() / double(windowRect.width());
		yscale = printer->pageRect().height() / double(windowRect.height());
		scale = qMin(xscale, yscale);

		painter.translate(-double(windowRect.topLeft().x())*scale, -double(windowRect.topLeft().y())*scale);


		if (windowRect.width() >= windowRect.height()) {
			rect = QRect((double(windowRect.topLeft().x())*scale),
				(double(windowRect.topLeft().y())*scale) + (double(windowRect.height()*scale)),
				printer->pageRect().width(), printer->pageRect().height());
		}
		else {
			rect = QRect((double(windowRect.topLeft().x())*scale) + (double(windowRect.width())*scale),
				(double(windowRect.topLeft().y())*scale),
				printer->pageRect().width(), printer->pageRect().height());

		}


		if (printerManager->IsCenterThePlot() == true) {

			if (windowRect.width() >= windowRect.height()) {
				painter.translate(0, printer->pageRect().height() / 2);
				painter.translate(0, -double(windowRect.height())*scale / 2);
			}
			else {

				painter.translate(printer->pageRect().width() / 2, 0);
				painter.translate(-double(windowRect.width())*scale / 2, 0);
			}
		}


		manager->GetActivatedWidget()->Print(&painter, scale);

		painter.eraseRect(rect);
		
		if (printerManager->IsCenterThePlot() == true) {
			QRect aboveRect;
			if (windowRect.width() >= windowRect.height()) {

				aboveRect = QRect(QPoint(rect.topLeft().x(),
					rect.topLeft().y() - double(printer->pageRect().height()) / 2 - double(windowRect.height())*scale / 2),
					QPoint(rect.bottomRight().x(), rect.topLeft().y() - double(windowRect.height()*scale)));

			}
			else {

				aboveRect = QRect(QPoint(rect.topLeft().x() - double(printer->pageRect().width()) / 2 - double(windowRect.width())*scale / 2,
					rect.topLeft().y()),
					QPoint(rect.topLeft().x() - double(windowRect.width()*scale),
						rect.bottomRight().y()));

			}

			painter.eraseRect(aboveRect);
		}
	}

	painter.end();

}


void ShPreviewDialog::PrintWidgetTemp(QPrinter *printer) {

	QPainter painter(printer);
	ShPrinterManager *printerManager = ShPrinterManager::GetInstance();
	ShWidgetManager *manager = ShWidgetManager::GetInstance();
	double xscale, yscale, scale;
	QRect drawRect;
	QRect windowRect;

	if (printerManager->GetWhatToPlot() == WhatToPlot::PlotDisplay) {

		windowRect = manager->GetActivatedWidget()->rect();
	}
	else {

		windowRect = this->ConvertWindowRect(printerManager->GetWindowPrevX(), printerManager->GetWindowPrevY(),
			printerManager->GetWindowCurrentX(), printerManager->GetWindowCurrentY());
	}

	xscale = printer->pageRect().width() / double(windowRect.width());
	yscale = printer->pageRect().height() / double(windowRect.height());
	scale = qMin(xscale, yscale);

	if (printerManager->GetWhatToPlot() == WhatToPlot::PlotWindow)
		painter.translate(-double(windowRect.topLeft().x())*scale, -double(windowRect.topLeft().y())*scale);

	drawRect = QRect(0, 0, double(windowRect.width())*scale, double(windowRect.height())*scale);
	


	if (printerManager->IsCenterThePlot() == true) {

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





	manager->GetActivatedWidget()->Print(&painter, scale);

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


QRect ShPreviewDialog::ConvertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();
	int prevX, prevY, currentX, currentY;

	manager->GetActivatedWidget()->ConvertEntityToDevice(windowPrevX, windowPrevY, prevX, prevY);
	manager->GetActivatedWidget()->ConvertEntityToDevice(windowCurrentX, windowCurrentY, currentX, currentY);

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