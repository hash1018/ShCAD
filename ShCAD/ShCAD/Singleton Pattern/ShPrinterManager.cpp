
#include "ShPrinterManager.h"
#include <stdlib.h>
#include <qprinterinfo.h>

ShPrinterManager* ShPrinterManager::instance = 0;


ShPrinterManager::ShPrinterManager()
	:isCenterThePlot(false), isSavedInfo(false), whatToPlot(WhatToPlot::PlotDisplay) {

	this->printerName = QPrinterInfo::defaultPrinterName();

}

ShPrinterManager::~ShPrinterManager() {

}

void ShPrinterManager::Destroy() {

	if (instance != 0)
		delete instance;


	instance = 0;
}

ShPrinterManager* ShPrinterManager::GetInstance() {

	if (instance == 0) {
		instance = new ShPrinterManager;
		atexit(Destroy);

	}
	return instance;

}


QString ShPrinterManager::GetWhatToPlotText() {
	QString str;

	if (this->whatToPlot == WhatToPlot::PlotDisplay) {
		str = "Display";
		return str;
	}

	if (this->whatToPlot == WhatToPlot::PlotWindow) {
		str = "Window";
		return str;
	}

	return str;
}

void ShPrinterManager::SetWhatToPlot(QString &whatToPlot) {

	if (whatToPlot == "Display") {
		this->whatToPlot = WhatToPlot::PlotDisplay;
		return;
	}
	if (whatToPlot == "Window") {
		this->whatToPlot = WhatToPlot::PlotWindow;
		return;
	}
}
