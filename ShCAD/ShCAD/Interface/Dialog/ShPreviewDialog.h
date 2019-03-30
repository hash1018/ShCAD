

#ifndef _SHPREVIEWDIALOG_H
#define _SHPREVIEWDIALOG_H

#include <qdialog.h>
class QPrinter;
class QPrintPreviewWidget;
class ShPreviewDialog : public QDialog {
	Q_OBJECT

private:
	QPrintPreviewWidget *preview;

private:
	QRect ConvertWindowRect(double windowPrevX, double windowPrevY, double windowCurrentX, double windowCurrentY);

public:
	ShPreviewDialog(QWidget *parent = 0);
	~ShPreviewDialog();

	private slots:
	void PrintWidget(QPrinter *printer);
	void PrintWidgetTemp(QPrinter *printer);

};

#endif //_SHPREVIEWDIALOG_H