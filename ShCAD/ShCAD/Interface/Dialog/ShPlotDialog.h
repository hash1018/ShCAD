
#ifndef _SHPLOTDIALOG_H
#define _SHPLOTDIALOG_H

#include <qdialog.h>

class QPrinter;
class QLabel;
class QGroupBox;
class QComboBox;
class QPushButton;
class QCheckBox;
class QSpinBox;
class ShPlotDialog : public QDialog {
	Q_OBJECT

private:
	double windowPrevX;
	double windowPrevY;
	double windowCurrentX;
	double windowCurrentY;

private:
	QGroupBox *printerGroupBox;
	QLabel *printerName;
	QComboBox *printerCombo;

	QGroupBox *plotAreaGroupBox;
	QLabel *whatToPlotLabel;
	QComboBox *whatToPlotCombo;
	QPushButton *windowButton;


	QGroupBox *numberOfCopiesGroupBox;
	QSpinBox *numberSpinBox;


	QCheckBox *centerThePlotCheckBox;


	QPushButton *printButton;
	QPushButton *pageSetupButton;
	QPushButton *cancelButton;
	QPushButton *previewButton;
	QPushButton *okButton;

	void CreateItems();
	void UpdatePrinterCombo();
	void UpdateWhatToPlotCombo();
	void ConnectSignals();

	void UpdatePrinterInfo();
	void SavePrinterInfo();
	QRect ConvertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY);

public:
	ShPlotDialog(QWidget *parent = 0);

	//Make sure instance of the class to be created in heap area.
	void Destroy();


	void SetWindowPrevXY(double windowPrevX, double windowPrevY);
	void SetWindowCurrentXY(double windowCurrentX, double windowCurrentY);

protected:
	~ShPlotDialog();


	private slots:
	void PrintButtonClicked();
	void PageSetupButtonClicked();
	void CancelButtonClicked();
	void PreviewButtonClicked();
	void OkButtonClicked();
	void WhatToPlotIndexChanged(int index);
	void WindowButtonClicked();

};

#endif //_SHPLOTDIALOG_H