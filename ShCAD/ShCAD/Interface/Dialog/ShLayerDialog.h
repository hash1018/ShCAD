

#ifndef _SHLAYERDIALOG_H
#define _SHLAYERDIALOG_H

#include <qdialog.h>
class QTableWidget;
class ShLayerTable;
class ShNotifyEvent;
class QTableWidgetItem;
class QPushButton;
class ShLayerDialog : public QDialog {
	Q_OBJECT

private:
	ShLayerTable *layerTable;
	QTableWidget *table;
	bool isItemChangedByUser;
	QPushButton *newLayerButton;
	QPushButton *deleteLayerButton;


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
	void CellDoubleClicked(int row, int column);
	void LayerNameChanged(QTableWidgetItem *item);
	void LineStyleComboIndexChanged(int);
	void NewLayerButtonClicked();
	void DeleteLayerButtonClicked();
};


#endif //_SHLAYERDIALOG_H