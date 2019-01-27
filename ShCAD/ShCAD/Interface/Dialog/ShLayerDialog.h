

#ifndef _SHLAYERDIALOG_H
#define _SHLAYERDIALOG_H

#include <qdialog.h>
class QTableWidget;
class ShLayerTable;
class ShNotifyEvent;
class ShLayerDialog : public QDialog {
	Q_OBJECT

private:
	ShLayerTable *layerTable;
	QTableWidget *table;

public:
	ShLayerDialog(ShLayerTable *layerTable, QWidget *parent = 0);
	~ShLayerDialog();

private:
	void UpdateLayerList();
	void UpdateColumnState(int row);
	void UpdateColumnName(int row);
	void UpdateColumnOnOff(int row);
	void UpdateColumnColor(int row);
	void UpdateColumnLineStyle(int row);

	void Notify(ShNotifyEvent *event);


protected:
	void resizeEvent(QResizeEvent *event);


	private slots:
	void CellClicked(int row, int column);
};


#endif //_SHLAYERDIALOG_H