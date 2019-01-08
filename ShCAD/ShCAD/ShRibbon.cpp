
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/


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

ShRibbonTab* ShRibbon::AddTab(const QString &title) {
	
	ShRibbonTab* shRibbonTab = new ShRibbonTab(this->tab);
	this->tab->addTab(shRibbonTab, title);
	
	return shRibbonTab;
}

ShRibbonTab* ShRibbon::AddTab(ShRibbonTab *tab) {

	this->tab->addTab(tab, tab->windowTitle());

	return tab;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShRibbonTab::ShRibbonTab(QWidget *parent)
	:QToolBar(parent) {

}

ShRibbonTab::ShRibbonTab(const QString& title, QWidget *parent)
	: QToolBar(parent) {

	this->setWindowTitle(title);

}

ShRibbonTab::~ShRibbonTab() {

}

ShColumnInRibbonTab* ShRibbonTab::AddColumn() {

	ShColumnInRibbonTab *widget = new ShColumnInRibbonTab(this,"");
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}

ShColumnInRibbonTab* ShRibbonTab::AddColumn(const QString& columnTitle) {

	ShColumnInRibbonTab *widget = new ShColumnInRibbonTab(this, columnTitle);
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}

ShColumnInRibbonTab* ShRibbonTab::AddColumn(const QString& columnTitle, int columnWidth) {

	ShColumnInRibbonTab *widget = new ShColumnInRibbonTab(this, columnTitle);
	widget->setFixedWidth(columnWidth);
	this->addWidget(widget);
	this->addSeparator();
	
	return widget;
}

ShColumnInRibbonTab* ShRibbonTab::AddColumn(ShColumnInRibbonTab *column) {

	this->addWidget(column);
	this->addSeparator();

	return column;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

ShColumnInRibbonTab::ShColumnInRibbonTab(QWidget *parent, const QString& title)
	:QWidget(parent), title(title) {
	
	this->area = BottomColumnTitleArea;
	
	this->layoutWidget = new QWidget(this);
	this->layoutWidget->setGeometry(0, 0, this->width(), this->height() - 27);
	
}

ShColumnInRibbonTab::ShColumnInRibbonTab(QWidget *parent, const QString &title, int width)
	:QWidget(parent), title(title) {

	this->area = BottomColumnTitleArea;
	this->setFixedWidth(width);

	this->layoutWidget = new QWidget(this);
	this->layoutWidget->setGeometry(0, 0, this->width(), this->height() - 27);
}

ShColumnInRibbonTab::~ShColumnInRibbonTab() {

}


void ShColumnInRibbonTab::SetColumnTitleArea(ColumnTitleArea area) {

	this->area = area;

	if (this->area == BottomColumnTitleArea)
		this->layoutWidget->setGeometry(0, 0, this->width(), this->height() - 27);
	else
		this->layoutWidget->setGeometry(0, 22, this->width(), this->height() - 27);

	this->update();
}

void ShColumnInRibbonTab::AddItem(QWidget *widget, const QRect &rect) {

	widget->setParent(this->layoutWidget);
	widget->setGeometry(rect);

}

void ShColumnInRibbonTab::SetColumnWidth(int width) {

	this->setFixedWidth(width);
	this->update();
}


void ShColumnInRibbonTab::paintEvent(QPaintEvent *event) {

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
		
	}
	else {

		pos = QPoint((this->width() / 2) - (width / 2), height);
		paint.drawText(pos, this->title);
		paint.setPen(QColor(195, 195, 195));
		paint.drawLine(5, height + 5, this->width() - 5, height + 5);
		

	}
}

#include <QResizeEvent>
void ShColumnInRibbonTab::resizeEvent(QResizeEvent *event) {

	QWidget::resizeEvent(event);

	if (this->area == BottomColumnTitleArea)
		this->layoutWidget->setGeometry(0, 0, event->size().width(), event->size().height() - 27);
	else
		this->layoutWidget->setGeometry(0, 22, event->size().width(), event->size().height() - 27);


}