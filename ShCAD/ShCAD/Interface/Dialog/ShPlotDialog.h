
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

private:
	void createItems();
	void updatePrinterCombo();
	void updateWhatToPlotCombo();
	void connectSignals();

	void updatePrinterInfo();
	void savePrinterInfo();
	QRect convertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY);

public:
	ShPlotDialog(QWidget *parent = nullptr);

	//Make sure instance of the class to be created in heap area.
	void destroy();


	void setWindowPrevXY(double windowPrevX, double windowPrevY);
	void setWindowCurrentXY(double windowCurrentX, double windowCurrentY);

protected:
	~ShPlotDialog();


	private slots:
	void printButtonClicked();
	void pageSetupButtonClicked();
	void cancelButtonClicked();
	void previewButtonClicked();
	void okButtonClicked();
	void whatToPlotIndexChanged(int index);
	void windowButtonClicked();

};

#endif //_SHPLOTDIALOG_H
