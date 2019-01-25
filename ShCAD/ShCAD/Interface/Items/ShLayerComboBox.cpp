

#include "ShLayerComboBox.h"
#include <qstandarditemmodel.h>
#include <qheaderview.h>


ShLayerDelegate::ShLayerDelegate(QWidget *parent)
	:QStyledItemDelegate(parent) {

}

ShLayerDelegate::~ShLayerDelegate() {

}

#include <qapplication.h>
#include <qpainter.h>
#include <qvariant.h>
void ShLayerDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{


	if (option.state & QStyle::State_HasFocus) {
		
		painter->fillRect(option.rect, option.palette.highlight());

		QPen oldPen = painter->pen();
		QPen pen(Qt::PenStyle::DotLine);
		pen.setColor(QColor(255, 255, 255));
		painter->setPen(pen);

		QRect rect = option.rect.adjusted(0, 0, -1, -1);
		painter->drawRect(rect);

		painter->setPen(oldPen);
	}


	//if (index.data().canConvert<TempLayer>() == true) {

	if (index.data(Qt::UserRole).canConvert<TempLayer>()) {
		TempLayer tempLayer = qvariant_cast<TempLayer> (index.data(Qt::UserRole));

		if (tempLayer.isActivated == false) {
			painter->drawText(option.rect, "false" + tempLayer.text);
		}
		else {
			painter->drawText(option.rect, "true" + tempLayer.text);
		}
	}
	//}
	
	else {
		painter->drawText(option.rect, index.data(1).toString());
	}
	
}

QSize ShLayerDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {

	return QSize(100, 17);
}



ShLayerView::ShLayerView(QWidget *parent)
	:QListView(parent) {

	
}

ShLayerView::~ShLayerView() {

}

#include <qmessagebox.h>
#include <QMouseEvent>
void ShLayerView::mousePressEvent(QMouseEvent *event) {
	
	
	//QMessageBox box;
	//box.setText(QString::number(this->currentIndex().row()));
	//box.exec();

	QModelIndex index = this->currentIndex();

	QRect rect = this->visualRect(index);
	QString text;
	if (event->x() <= rect.topLeft().x() + 20) {
		text = "1";
	}
	else if (event->x() > rect.topLeft().x() + 20 && event->x() <= rect.topLeft().x() + 40) {
		text = "2";
	}
	else if (event->x() > rect.topLeft().x() + 40 && event->x() <= rect.topLeft().x() + 60) {
		text = "3";
	}
	else {
		text = "4";
	}

	QMessageBox box;
	box.setText(QString::number(index.row()) + text);
	box.exec();



}


ShLayerComboBox::ShLayerComboBox(QWidget *parent)
	:QComboBox(parent) {

	this->setFixedWidth(150);

	
	
	//QStandardItemModel *model = new QStandardItemModel(this);
	//this->setModel(model);
	
	//for (int row = 0; row < 4; ++row) {
	//	for (int column = 0; column < 4; ++column) {
	//		QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
	//		model->setItem(row, column, item);
	//	}
	//}

	ShLayerView *view = new ShLayerView(this);
	view->setItemDelegate(new ShLayerDelegate(this));
	this->setView(view);
	
	
	
	
	
	
	//this->addItem("hi");
	//this->addItem("hello   ");
	
	
	QVariant var;
	var.setValue(this->layer);

	this->layer2.isActivated = false;
	this->layer2.text = "hihihihi";
	QVariant var2;
	var2.setValue(this->layer2);

	
	
	this->addItem("hi", var);
	this->addItem("hello", var2);

	if (this->currentData(Qt::UserRole).canConvert<TempLayer>()) {
		TempLayer tempLayer = this->currentData(Qt::UserRole).value<TempLayer>();

		qDebug("ghgfhfghfgh");
	}
	
	
}

ShLayerComboBox::~ShLayerComboBox() {


}

void ShLayerComboBox::paintEvent(QPaintEvent *event) {

	/*
	QStylePainter painter(this);
	painter.setPen(palette().color(QPalette::Text));

	// draw the combobox frame, focusrect and selected etc.
	QStyleOptionComboBox opt;
	initStyleOption(&opt);
	painter.drawComplexControl(QStyle::CC_ComboBox, opt);

	//here is where the customization start!!!
	QRect rect = opt.rect.adjusted(1, 1, -20, -2); //compensate for frame and arrow 

	painter.drawText(0,0, "he");
	*/
	QComboBox::paintEvent(event);
}
