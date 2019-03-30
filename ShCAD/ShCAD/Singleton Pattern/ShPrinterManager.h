
#ifndef _SHPRINTERMANAGER_H
#define _SHPRINTERMANAGER_H

#include <qstring.h>
#include <qprinter.h>
#include "ShVariable.h"

class ShPrinterManager {

private:
	QPrinter printer;
	QString printerName;
	WhatToPlot whatToPlot;

	bool isSavedInfo;
	bool isCenterThePlot;

	double windowPrevX;
	double windowPrevY;
	double windowCurrentX;
	double windowCurrentY;

private:
	ShPrinterManager();
	~ShPrinterManager();
	static void Destroy();

	static ShPrinterManager* instance;

public:
	static ShPrinterManager* GetInstance();

	bool IsSavedInfo() const { return this->isSavedInfo; }
	bool IsCenterThePlot() const { return this->isCenterThePlot; }
	QString& GetPrinterName() const { return const_cast<QString&>(this->printerName); }
	WhatToPlot GetWhatToPlot() const { return this->whatToPlot; }
	QString GetWhatToPlotText();

	double GetWindowPrevX() const { return this->windowPrevX; }
	double GetWindowPrevY() const { return this->windowPrevY; }
	double GetWindowCurrentX() const { return this->windowCurrentX; }
	double GetWindowCurrentY() const { return this->windowCurrentY; }


	QPrinter* Printer() { return &(this->printer); }



	void SetIsSavedInfo(bool isSavedInfo) { this->isSavedInfo = isSavedInfo; }
	void SetIsCenterThePlot(bool isCenterThePlot) { this->isCenterThePlot = isCenterThePlot; }
	void SetPrinterName(QString& printerName) { this->printerName = printerName; }
	void SetWhatToPlot(WhatToPlot whatToPlot) { this->whatToPlot = whatToPlot; }
	void SetWhatToPlot(QString &whatToPlot);
	void SetWindowPrevXY(double windowPrevX, double windowPrevY) { this->windowPrevX = windowPrevX; this->windowPrevY = windowPrevY; }
	void SetWindowCurrentXY(double windowCurrentX, double windowCurrentY) { this->windowCurrentX = windowCurrentX; this->windowCurrentY = windowCurrentY; }
};



#endif //_PRINTERMANAGER_H