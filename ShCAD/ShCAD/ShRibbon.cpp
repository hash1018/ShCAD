

#include "ShRibbon.h"
#include <qtabwidget.h>
#include <qpainter.h>

ShRibbon::ShRibbon(QWidget *parent)
	:QToolBar(parent) {

	this->setMovable(false);
	this->setFloatable(false);

	this->tab = new QTabWidget(this);
	this->addWidget(this->tab);
}

ShRibbon::ShRibbon(const QSize& size, QWidget *parent)
	:QToolBar(parent) {

	this->setFixedSize(size);

	this->setMovable(false);
	this->setFloatable(false);

	this->tab = new QTabWidget(this);
	this->addWidget(this->tab);
}

ShRibbon::ShRibbon(int height, QWidget *parent)
	:QToolBar(parent) {

	this->setFixedHeight(height);

	this->setMovable(false);
	this->setFloatable(false);

	this->tab = new QTabWidget(this);
	this->addWidget(this->tab);
}

ShRibbon::~ShRibbon() {


}

ShWidgetInTab* ShRibbon::AddTab(const QString &title) {
	
	ShWidgetInTab* shWidgetInTab = new ShWidgetInTab(this->tab);
	this->tab->addTab(shWidgetInTab, title);
	
	return shWidgetInTab;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShWidgetInTab::ShWidgetInTab(QWidget *parent)
	:QToolBar(parent) {

}

ShWidgetInTab::~ShWidgetInTab() {

}

ShColumnWidget* ShWidgetInTab::AddColumn() {

	ShColumnWidget *widget = new ShColumnWidget(this,"");
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}

ShColumnWidget* ShWidgetInTab::AddColumn(const QString& columnTitle) {

	ShColumnWidget *widget = new ShColumnWidget(this, columnTitle);
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}

ShColumnWidget* ShWidgetInTab::AddColumn(const QString& columnTitle, int columnWidth) {

	ShColumnWidget *widget = new ShColumnWidget(this, columnTitle);
	widget->setFixedWidth(columnWidth);
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

ShColumnWidget::ShColumnWidget(QWidget *parent, const QString& title)
	:QWidget(parent), title(title) {
	this->index = 0;
	this->area = BottomColumnTitleArea;
	this->repaint();
	qDebug("left %d top %d in constructor index %d", this->layoutRect.left(), this->layoutRect.top(), index++);
	
}

ShColumnWidget::~ShColumnWidget() {

}


void ShColumnWidget::SetColumnTitleArea(ColumnTitleArea area) {

	this->area = area;
	this->repaint();
}

void ShColumnWidget::AddItem(QWidget *widget, const QRect &rect) {

	this->update();

	widget->setParent(this);



	qDebug("left %d top %d in AddItem  index %d", this->layoutRect.left(), this->layoutRect.top(), index++);
	widget->setGeometry(this->layoutRect.x() + rect.x(),
		this->layoutRect.y() + rect.y(), rect.width(), rect.height());

}


void ShColumnWidget::paintEvent(QPaintEvent *event) {

	//QWidget::paintEvent(event);

	QPainter paint(this);

	QFontMetrics fm(paint.font());

	int width = fm.width(this->title);
	int height = fm.height();
	QPoint pos;

	if (this->area == BottomColumnTitleArea) {
		pos = QPoint((this->width() / 2) - (width / 2),this->height() - (height/2));
		paint.drawText(pos, this->title);
		paint.setPen(QColor(195, 195, 195));
		paint.drawLine(5, this->height() - height-10, this->width() - 5, this->height() - height-10);
		this->layoutRect = QRect(0, 0, this->width(), this->height() - height - 15);
		paint.fillRect(this->layoutRect, QColor(0, 0, 0));
		qDebug("left %d top %d in paintEvent bottom  index %d", this->layoutRect.left(), this->layoutRect.top(), index++);
	}
	else {
		pos = QPoint((this->width() / 2) - (width / 2), height);
		paint.drawText(pos, this->title);
		paint.setPen(QColor(195, 195, 195));
		paint.drawLine(5, height + 5, this->width() - 5, height + 5);
		this->layoutRect = QRect(0, height+10, this->width(), this->height() - height - 10);
		paint.fillRect(this->layoutRect.x(),this->layoutRect.y(),this->layoutRect.width(),this->layoutRect.height(), QColor(0, 0, 0));
		
		qDebug("left %d top %d in paintEvent top index %d", this->layoutRect.left(), this->layoutRect.top(), index++);

	}
}