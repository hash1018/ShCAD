
#include "ShLayerComboBox.h"
#include <qpainter.h>
#include <qvariant.h>
#include <qstylepainter.h>
#include <QMouseEvent>
#include <qcolordialog.h>
#include <qbitmap.h>
#include "Base\ShLayerTable.h"


ShLayerDelegate::ShLayerDelegate(QWidget *parent)
	:QStyledItemDelegate(parent) {

}

ShLayerDelegate::~ShLayerDelegate() {

}

void ShLayerDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

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

	if (index.data(Qt::UserRole).canConvert<ShLayer*>()) {
		ShLayer *layer = qvariant_cast<ShLayer*>(index.data(Qt::UserRole));


		QRect rect = option.rect.adjusted(0, 0, -183, 0);
		QPixmap pix(17, 17);

		if (layer->isTurnOn() == true)
			pix.load(":Image/LayerTurnOn.png");
		else
			pix.load(":Image/LayerTurnOff.png");

		QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
		pix.setMask(mask);

		painter->drawPixmap(rect, pix);


		rect = option.rect.adjusted(22, 2, -165, -3);
		ShColor color = layer->getPropertyData().getColor();
		painter->fillRect(rect, QColor(color.getRed(), color.getGreen(), color.getBlue()));

		rect = option.rect.adjusted(40, 0, 0, 0);
		painter->drawText(rect, layer->getName());
	}

}

QSize ShLayerDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {

	return QSize(200, 17);
}


//////////////////////////////////////////////

ShLayerComboBox::ShLayerComboBox(QWidget *parent)
	:QComboBox(parent), layerTable(nullptr), layerComboSelChangedByUser(true), layerComboIndex(0) {

	this->setFixedWidth(200);
	this->setItemDelegate(new ShLayerDelegate(this));

	this->view()->viewport()->installEventFilter(this);
}

ShLayerComboBox::~ShLayerComboBox() {

}

void ShLayerComboBox::setLayerComboCurrentIndex(int index) {

	this->layerComboSelChangedByUser = false;
	this->setCurrentIndex(index);
	this->layerComboSelChangedByUser = true;
	this->layerComboIndex = index;
}

void ShLayerComboBox::setLayerComboCurrentIndex(ShLayer *layer) {

	this->layerComboSelChangedByUser = false;
	int index = this->layerTable->getIndex(layer);
	this->setCurrentIndex(index);
	this->layerComboSelChangedByUser = true;
	this->layerComboIndex = index;
}

void ShLayerComboBox::updateLayerCombo() {

	this->layerComboSelChangedByUser = false;

	this->clear();

	for (int i = 0; i < this->layerTable->getSize(); i++) {

		ShLayer *layer = this->layerTable->getLayer(i);
		QVariant var;
		var.setValue(layer);
		this->addItem("", var);
	}


	this->layerComboSelChangedByUser = true;
}

void ShLayerComboBox::paintEvent(QPaintEvent *event) {

	QStylePainter painter(this);
	painter.setPen(palette().color(QPalette::Text));

	QStyleOptionComboBox opt;
	initStyleOption(&opt);
	painter.drawComplexControl(QStyle::CC_ComboBox, opt);

	QRect rect = opt.rect.adjusted(4, 4, -20, -2);

	if (this->layerTable == 0)
		return;

	if (this->layerComboIndex == -1)
		return;

	ShLayer *currentLayer = this->layerTable->getLayer(this->layerComboIndex);

	int width = rect.width();

	QRect drawRect = rect.adjusted(0, 0, 16 - width, 0);
	QPixmap pix;

	if (currentLayer->isTurnOn() == true)
		pix.load(":Image/LayerTurnOn.png");
	else
		pix.load(":Image/LayerTurnOff.png");

	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	painter.drawPixmap(drawRect, pix);


	drawRect = rect.adjusted(22, 2, 32 - width, -3);
	ShColor color = currentLayer->getPropertyData().getColor();
	painter.fillRect(drawRect, QColor(color.getRed(), color.getGreen(), color.getBlue()));

	drawRect = rect.adjusted(40, 0, 0, 0);
	painter.drawText(drawRect, currentLayer->getName());
}

bool ShLayerComboBox::eventFilter(QObject *obj, QEvent *event) {


	if (event->type() == QEvent::Type::MouseButtonDblClick ||
		event->type() == QEvent::Type::MouseButtonPress ||
		event->type() == QEvent::Type::MouseButtonRelease) {

		QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);

		QModelIndex index = this->view()->currentIndex();

		if (index.row() < 0)
			return true;

		QRect rect = this->view()->visualRect(index);

		if (mouseEvent->x() <= rect.topLeft().x() + 17) {

			ShLayer *layer = this->layerTable->getLayer(index.row());

			bool turnOn;

			if (layer->isTurnOn() == true)
				turnOn = false;
			else
				turnOn = true;

			emit layerTurnChanged(layer, turnOn);
		}
		else if (mouseEvent->x() > rect.topLeft().x() + 17 && mouseEvent->x() <= rect.topLeft().x() + 34) {
			QColorDialog dialog;

			if (dialog.exec() == QDialog::Accepted) {

				QColor color = dialog.currentColor();

				ShColor color2 = ShColor(color.red(), color.green(), color.blue(), ShColor::Type::ByLayer);

				emit layerColorChanged(this->layerTable->getLayer(index.row()), color2);
			}
		}
		else {

			this->setLayerComboCurrentIndex(index.row());
			emit currentLayerChanged(this->layerTable->getLayer(index.row()));
			this->hidePopup();
		}


		return true;
	}


	return QComboBox::eventFilter(obj, event);
}