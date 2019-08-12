
#ifndef _SHLAYERCOMBOBOX_H
#define _SHLAYERCOMBOBOX_H

#include <qcombobox.h>
#include <qlistview.h>
#include <qstyleditemdelegate.h>
#include "Base\ShLayer.h"

class ShColor;
class ShLayerTable;

class ShLayerDelegate : public QStyledItemDelegate {
	Q_OBJECT

public:
	ShLayerDelegate(QWidget *parent = nullptr);
	~ShLayerDelegate();

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

///////////////////////////////////////////////

class ShLayerComboBox : public QComboBox {
	Q_OBJECT

private:
	const ShLayerTable *layerTable;
	bool layerComboSelChangedByUser;
	int layerComboIndex;

public:
	ShLayerComboBox(QWidget *parent = nullptr);
	~ShLayerComboBox();

	void setLayerComboCurrentIndex(int index);
	void setLayerComboCurrentIndex(ShLayer *layer);
	void updateLayerCombo();

public:
	void setLayerTable(const ShLayerTable *layerTable) { this->layerTable = layerTable; }

signals:
	void currentLayerChanged(ShLayer *layer);
	void layerTurnChanged(ShLayer *layer, bool turnOn);
	void layerColorChanged(ShLayer *layer, const ShColor &color);

protected:
	void paintEvent(QPaintEvent *event);
	bool eventFilter(QObject *obj, QEvent *event);
	
};

#endif //_SHLAYERCOMBOBOX_H