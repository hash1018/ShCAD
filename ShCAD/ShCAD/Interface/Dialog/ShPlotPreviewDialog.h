

#ifndef _SHPLOTPREVIEWDIALOG_H
#define _SHPLOTPREVIEWDIALOG_H

#include <qdialog.h>

class QPrinter;
class QPrintPreviewWidget;

class ShPlotPreviewDialog : public QDialog {

private:
	QPrintPreviewWidget *preview;

public:
	ShPlotPreviewDialog(QWidget *parent = nullptr);
	~ShPlotPreviewDialog();

	private slots:
	void printWidget(QPrinter *printer);
	

private:
	QRect convertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY);

};

#endif //_SHPLOTPREVIEWDIALOG_H