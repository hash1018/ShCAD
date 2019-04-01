
#include "ShPlotDialog.h"
#include <qprinterinfo.h>
#include <qprinter.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qspinbox.h>

//#include "SettingManager.h"
#include <qpagesetupdialog.h>

#include "Singleton Pattern\ShPrinterManager.h"

ShPlotDialog::ShPlotDialog(QWidget *parent)
	:QDialog(parent), windowPrevX(0), windowPrevY(0), windowCurrentX(0), windowCurrentY(0) {

	this->setMinimumSize(450, 600);
	this->setMaximumSize(450, 600);


	this->CreateItems();
	this->ConnectSignals();
	this->UpdatePrinterInfo();

}

ShPlotDialog::~ShPlotDialog() {


}

void ShPlotDialog::Destroy() {

	delete this;
}

void ShPlotDialog::CreateItems() {

	this->printerGroupBox = new QGroupBox("Printer", this);
	this->printerGroupBox->setGeometry(20, 40, this->width() - 40, 60);

	this->printerName = new QLabel("Name:", this);
	this->printerName->setGeometry(40, 60, 40, 20);

	this->printerCombo = new QComboBox(this);
	this->printerCombo->setGeometry(100, 60, this->width() - 140, 20);
	this->printerCombo->setIconSize(QSize(17, 17));

	this->UpdatePrinterCombo();

	this->plotAreaGroupBox = new QGroupBox("Plot Area", this);
	this->plotAreaGroupBox->setGeometry(20, 110, this->width() - 200, 95);

	this->whatToPlotLabel = new QLabel("What to plot:", this);
	this->whatToPlotLabel->setGeometry(30, 135, 100, 20);

	this->whatToPlotCombo = new QComboBox(this);
	this->whatToPlotCombo->setGeometry(30, 160, 100, 20);

	this->windowButton = new QPushButton("Window <", this);
	this->windowButton->setGeometry(150, 158, 100, 25);
	this->windowButton->hide();

	this->UpdateWhatToPlotCombo();


	this->numberOfCopiesGroupBox = new QGroupBox("Number of copies", this);
	this->numberOfCopiesGroupBox->setGeometry(this->width() - 160, 110, 140, 60);

	this->numberSpinBox = new QSpinBox(this);
	this->numberSpinBox->setGeometry(this->width() - 100, 135, 40, 25);
	this->numberSpinBox->setMinimum(1);

	this->centerThePlotCheckBox = new QCheckBox("Center the plot", this);
	this->centerThePlotCheckBox->setGeometry(20, 205, 140, 25);

	this->pageSetupButton = new QPushButton("Page Setup", this);
	this->pageSetupButton->setGeometry(this->width() - 160, 180, 140, 25);

	this->okButton = new QPushButton("Ok", this);
	this->okButton->setGeometry(120, this->height() - 40, 100, 25);

	this->printButton = new QPushButton("Print", this);
	this->printButton->setGeometry(230, this->height() - 40, 100, 25);

	this->cancelButton = new QPushButton("Cancel", this);
	this->cancelButton->setGeometry(340, this->height() - 40, 100, 25);

	this->previewButton = new QPushButton("Preview", this);
	this->previewButton->setGeometry(10, this->height() - 40, 100, 25);

}

void ShPlotDialog::ConnectSignals() {

	connect(this->printButton, SIGNAL(released()), SLOT(PrintButtonClicked()));
	connect(this->pageSetupButton, SIGNAL(released()), SLOT(PageSetupButtonClicked()));
	connect(this->cancelButton, SIGNAL(released()), SLOT(CancelButtonClicked()));
	connect(this->previewButton, SIGNAL(released()), SLOT(PreviewButtonClicked()));
	connect(this->okButton, SIGNAL(released()), SLOT(OkButtonClicked()));

	connect(this->whatToPlotCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(WhatToPlotIndexChanged(int)));

	connect(this->windowButton, SIGNAL(released()), SLOT(WindowButtonClicked()));
}

void ShPlotDialog::UpdatePrinterInfo() {
	
	ShPrinterManager *manager = ShPrinterManager::GetInstance();
	QPrinter *printer = manager->Printer();

	printer->setCopyCount(1);

	this->centerThePlotCheckBox->setChecked(manager->IsCenterThePlot());
	this->printerCombo->setCurrentIndex(this->printerCombo->findText(manager->GetPrinterName()));
	this->whatToPlotCombo->setCurrentIndex(this->whatToPlotCombo->findText(manager->GetWhatToPlotText()));
	this->windowPrevX = manager->GetWindowPrevX();
	this->windowPrevY = manager->GetWindowPrevY();
	this->windowCurrentX = manager->GetWindowCurrentX();
	this->windowCurrentY = manager->GetWindowCurrentY();
	
}

void ShPlotDialog::UpdateWhatToPlotCombo() {

	this->whatToPlotCombo->clear();

	this->whatToPlotCombo->addItem("Display");
	this->whatToPlotCombo->addItem("Window");


}


void ShPlotDialog::UpdatePrinterCombo() {
	
	this->printerCombo->clear();

	//QString dir = GetImagePath();
	//QString filePath;
	//filePath = dir + "\\Print.bmp";
	//QIcon icon(filePath);

	QStringList names = QPrinterInfo::availablePrinterNames();

	for (int i = 0; i < names.size(); i++) {

	//	this->printerCombo->addItem(icon, names[i]);
		this->printerCombo->addItem(names[i]);
	}

	this->printerCombo->setCurrentIndex(this->printerCombo->findText(QPrinterInfo::defaultPrinterName()));
	
}





#include "Singleton Pattern\ShWidgetManager.h"
#include <qpainter.h>
#include "Interface\ShGraphicView.h"
void ShPlotDialog::PrintButtonClicked() {
	
	ShPrinterManager *printerManager = ShPrinterManager::GetInstance();
	ShGraphicView *view = ShWidgetManager::GetInstance()->GetActivatedWidget();
	QPrinter *printer = printerManager->Printer();

	printer->setCopyCount(this->numberSpinBox->value());
	printer->setPrinterName(this->printerCombo->currentText());

	this->SavePrinterInfo();



	QPainter painter(printer);
	double xscale, yscale, scale;
	QRect drawRect;
	QRect windowRect;

	if (printerManager->GetWhatToPlot() == WhatToPlot::PlotDisplay) {

		windowRect = view->rect();
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





	view->Print(&painter, scale);

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

	this->close();
	
}

void ShPlotDialog::PageSetupButtonClicked() {

	ShPrinterManager *printerManager = ShPrinterManager::GetInstance();
	QPrinter *printer = printerManager->Printer();

	QPageSetupDialog dlg(printer, this);
	dlg.exec();

}

void ShPlotDialog::CancelButtonClicked() {

	this->close();

}

void ShPlotDialog::OkButtonClicked() {

	this->SavePrinterInfo();

}



#include "ShPreviewDialog.h"
void ShPlotDialog::PreviewButtonClicked() {

	this->SavePrinterInfo();

	ShPreviewDialog preview(this);
	preview.exec();
}


void ShPlotDialog::WhatToPlotIndexChanged(int index) {

	if (this->whatToPlotCombo->currentText() == "Window")
		this->windowButton->show();
	else
		this->windowButton->hide();

}

#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "ActionHandler\ShActionHandlerManager.h"
#include "ActionHandler\ShPlotAreaSelectAction.h"
void ShPlotDialog::WindowButtonClicked() {
	
	ShGraphicView *view = ShWidgetManager::GetInstance()->GetActivatedWidget();

	ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionPlotAreaSelect);
	view->ChangeCurrentAction(strategy);
	ShActionHandler *action = const_cast<ShActionHandler*>(view->actionHandlerManager->GetCurrentAction());

	ShPlotAreaSelectAction *plotAreaSelectAction = dynamic_cast<ShPlotAreaSelectAction*>(action);
	plotAreaSelectAction->SetPlotDialog(this);
	this->setVisible(false);


}


void ShPlotDialog::SetWindowPrevXY(double windowPrevX, double windowPrevY) {

	this->windowPrevX = windowPrevX;
	this->windowPrevY = windowPrevY;

}

void ShPlotDialog::SetWindowCurrentXY(double windowCurrentX, double windowCurrentY) {

	this->windowCurrentX = windowCurrentX;
	this->windowCurrentY = windowCurrentY;

}

QRect ShPlotDialog::ConvertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY) {
	
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

void ShPlotDialog::SavePrinterInfo() {

	ShPrinterManager *manager = ShPrinterManager::GetInstance();

	manager->SetIsSavedInfo(true);
	manager->SetIsCenterThePlot(this->centerThePlotCheckBox->isChecked());
	manager->SetPrinterName(this->printerCombo->currentText());
	manager->SetWhatToPlot(this->whatToPlotCombo->currentText());
	manager->SetWindowPrevXY(this->windowPrevX, this->windowPrevY);
	manager->SetWindowCurrentXY(this->windowCurrentX, this->windowCurrentY);

}