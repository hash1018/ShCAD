

#ifndef _SHLAYERCOMBOBOX_H
#define _SHLAYERCOMBOBOX_H

#include <qcombobox.h>
#include <qlistview.h>
#include <qstyleditemdelegate.h>


class ShLayerDelegate : public QStyledItemDelegate{
	Q_OBJECT
public:
	ShLayerDelegate(QWidget *parent = 0);
	~ShLayerDelegate();

	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
	QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

};

class ShLayerComboBox;
class ShLayerView : public QListView {
	Q_OBJECT
private:
	ShLayerComboBox *comboBox;
public:
	ShLayerView(ShLayerComboBox *comboBox, QWidget *parent = 0);
	~ShLayerView();

protected:
	void mousePressEvent(QMouseEvent *event);

signals:
	void CurrentIndexChanged(int);
	void LayerTurnChanged();
	
};

class ShLayerTable;
class ShLayerComboBox : public QComboBox {
	Q_OBJECT
		friend class ShLayerView;
private:
	ShLayerView *view;
	ShLayerTable *layerTable;
	bool layerComboSelChangedByUser;
	int layerComboIndex;

public:
	ShLayerComboBox(QWidget *parent = 0);
	~ShLayerComboBox();

	void SetLayerTable(ShLayerTable *layerTable);
	void Synchronize();
	
	
private:
	void SetLayerComboCurrentIndex(int index);
	void UpdateLayerCombo();

protected:
	void paintEvent(QPaintEvent *event);
	

	private slots:
	void ComboSelChanged(int);
	void LayerTurnChanged();

};

#endif //_SHLAYERCOMBOBOX_H