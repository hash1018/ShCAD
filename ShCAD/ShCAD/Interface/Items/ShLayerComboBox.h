

#ifndef _SHLAYERCOMBOBOX_H
#define _SHLAYERCOMBOBOX_H

#include <qcombobox.h>
#include <qlistview.h>
#include <qstyleditemdelegate.h>
#include <qmetatype.h>
class TempLayer {
	
public:
	bool isActivated;
	QString text;
	
	TempLayer() :isActivated(true) { text = "Hello"; }
	~TempLayer() {}
	TempLayer(const TempLayer& other) 
		:isActivated(other.isActivated),text(other.text) {
	}
	TempLayer& operator=(const TempLayer& other) { this->isActivated = other.isActivated; this->text = other.text; return *this; }
};

Q_DECLARE_METATYPE(TempLayer)

class ShLayerDelegate : public QStyledItemDelegate{
	Q_OBJECT
public:
	ShLayerDelegate(QWidget *parent = 0);
	~ShLayerDelegate();

	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
	QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

};

class ShLayerView : public QListView {
	Q_OBJECT
public:
	ShLayerView(QWidget *parent = 0);
	~ShLayerView();

protected:
	void mousePressEvent(QMouseEvent *event);

	
};

class ShLayerComboBox : public QComboBox {
	Q_OBJECT
public:
	ShLayerComboBox(QWidget *parent = 0);
	~ShLayerComboBox();

	

	TempLayer layer;
	TempLayer layer2;
protected:
	void paintEvent(QPaintEvent *event);
	

	
};

#endif //_SHLAYERCOMBOBOX_H