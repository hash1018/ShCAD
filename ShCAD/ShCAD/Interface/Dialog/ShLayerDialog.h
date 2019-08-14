
#ifndef _SHLAYERDIALOG_H
#define _SHLAYERDIALOG_H

#include <qdialog.h>
#include "Chain of Responsibility\ShChain.h"

class QTableWidget;
class QTableWidgetItem;
class QPushButton;
class ShLayerTable;


class ShLayerDialog : public QDialog , public ShChain {
	Q_OBJECT

private:
	const ShLayerTable *layerTable;
	QTableWidget *table;
	bool isItemChangedByUser;
	QPushButton *createLayerButton;
	QPushButton *deleteLayerButton;

public:
	ShLayerDialog(const ShLayerTable *layerTable, ShChain *chain, QWidget *parent = nullptr);
	~ShLayerDialog();

private:
	void updateLayerTable();
	void updateStateColumn(int row);
	void updateNameColumn(int row);
	void updateTurnColumn(int row);
	void updateColorColumn(int row);
	void updateLineStyleColumn(int row);

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void cellClicked(int row, int column);
	void cellDoubleClicked(int row, int column);
	void layerNameChanged(QTableWidgetItem *item);
	void lineStyleComboIndexChanged(int index);
	void createLayerButtonClicked();
	void deleteLayerButtonClicked();

};

#endif //_SHLAYERDIALOG_H