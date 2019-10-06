
#ifndef _SHPLOTMANAGER_H
#define _SHPLOTMANAGER_H

#include <qstring.h>
#include <qprinter.h>
#include "Base\ShVariable.h"
#include "Base\ShSingleton.h"

class ShPlotManager {
	
	DeclareSingleton(ShPlotManager)

private:
	QPrinter printer;
	QString printerName;
	WhatToPlot whatToPlot;

	bool savedInfo;
	bool centerThePlot;

	double windowPrevX;
	double windowPrevY;
	double windowCurrentX;
	double windowCurrentY;

public:

	void setIsSavedInfo(bool savedInfo) { this->savedInfo = savedInfo; }
	void setIsCenterThePlot(bool centerThePlot) { this->centerThePlot = centerThePlot; }
	void setPrinterName(const QString& printerName) { this->printerName = printerName; }
	void setWhatToPlot(WhatToPlot whatToPlot) { this->whatToPlot = whatToPlot; }
	void setWhatToPlot(QString &whatToPlot);
	void setWindowPrevXY(double windowPrevX, double windowPrevY) { this->windowPrevX = windowPrevX; this->windowPrevY = windowPrevY; }
	void setWindowCurrentXY(double windowCurrentX, double windowCurrentY) { this->windowCurrentX = windowCurrentX; this->windowCurrentY = windowCurrentY; }

public:
	inline bool isSavedInfo() const { return this->savedInfo; }
	inline bool isCenterThePlot() const { return this->centerThePlot; }
	inline const QString& getPrinterName() const { return this->printerName; }
	inline WhatToPlot getWhatToPlot() const { return this->whatToPlot; }
	QString getWhatToPlotText();

	inline double getWindowPrevX() const { return this->windowPrevX; }
	inline double getWindowPrevY() const { return this->windowPrevY; }
	inline double getWindowCurrentX() const { return this->windowCurrentX; }
	inline double getWindowCurrentY() const { return this->windowCurrentY; }
	inline QPrinter* getPrinter() { return &(this->printer); }

};

#endif //_SHPLOTMANAGER_H