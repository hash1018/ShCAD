
#include "ShPlotManager.h"
#include <qprinterinfo.h>

ShPlotManager::ShPlotManager()
	:centerThePlot(false), savedInfo(false), whatToPlot(WhatToPlot::PlotDisplay) {

	this->printerName = QPrinterInfo::defaultPrinterName();
}

ShPlotManager::~ShPlotManager() {

}

QString ShPlotManager::getWhatToPlotText() {
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

void ShPlotManager::setWhatToPlot(QString &whatToPlot) {

	if (whatToPlot == "Display") {
		this->whatToPlot = WhatToPlot::PlotDisplay;
		return;
	}
	if (whatToPlot == "Window") {
		this->whatToPlot = WhatToPlot::PlotWindow;
		return;
	}
}
