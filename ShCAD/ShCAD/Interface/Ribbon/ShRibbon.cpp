
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

ShRibbon::ShRibbon(ShChain *chain, QWidget *parent)
	:QToolBar(parent), ShChain(chain) {

	this->setMovable(false);
	this->setFloatable(false);

	this->tab = new QTabWidget(this);
	this->addWidget(this->tab);
}

ShRibbon::ShRibbon(ShChain *chain, const QSize& size, QWidget *parent)
	:QToolBar(parent), ShChain(chain) {

	this->setFixedSize(size);

	this->setMovable(false);
	this->setFloatable(false);

	this->tab = new QTabWidget(this);
	this->addWidget(this->tab);
}

ShRibbon::ShRibbon(ShChain *chain, int height, QWidget *parent)
	:QToolBar(parent), ShChain(chain) {

	this->setFixedHeight(height);

	this->setMovable(false);
	this->setFloatable(false);

	this->tab = new QTabWidget(this);
	this->addWidget(this->tab);

}

ShRibbon::~ShRibbon() {


}

ShRibbonTab* ShRibbon::addTab(const QString &title) {

	ShRibbonTab* shRibbonTab = new ShRibbonTab(this, this->tab);
	this->tab->addTab(shRibbonTab, title);

	return shRibbonTab;
}

ShRibbonTab* ShRibbon::addTab(ShRibbonTab *tab) {

	this->tab->addTab(tab, tab->windowTitle());

	return tab;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ShRibbonTab::ShRibbonTab(ShChain *chain, QWidget *parent)
	:QToolBar(parent), ShChain(chain) {

}

ShRibbonTab::ShRibbonTab(const QString& title, ShChain *chain, QWidget *parent)
	: QToolBar(parent), ShChain(chain) {

	this->setWindowTitle(title);

}

ShRibbonTab::~ShRibbonTab() {

}

ShPanelInRibbonTab* ShRibbonTab::addPanel() {

	ShPanelInRibbonTab *widget = new ShPanelInRibbonTab(this, this, "");
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}

ShPanelInRibbonTab* ShRibbonTab::addPanel(const QString& columnTitle) {

	ShPanelInRibbonTab *widget = new ShPanelInRibbonTab(this, this, columnTitle);
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}

ShPanelInRibbonTab* ShRibbonTab::addPanel(const QString& columnTitle, int columnWidth) {

	ShPanelInRibbonTab *widget = new ShPanelInRibbonTab(this, this, columnTitle);
	widget->setFixedWidth(columnWidth);
	this->addWidget(widget);
	this->addSeparator();

	return widget;
}

ShPanelInRibbonTab* ShRibbonTab::addPanel(ShPanelInRibbonTab *panel) {

	this->addWidget(panel);
	this->addSeparator();

	return panel;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

ShPanelInRibbonTab::ShPanelInRibbonTab(ShChain *chain, QWidget *parent, const QString& title)
	:ShChain(chain), QWidget(parent), title(title) {

	this->area = BottomPanelTitleArea;

	this->layoutWidget = new QWidget(this);
	this->layoutWidget->setGeometry(0, 0, this->width(), this->height() - 27);

}

ShPanelInRibbonTab::ShPanelInRibbonTab(ShChain *chain, QWidget *parent, const QString &title, int width)
	:ShChain(chain), QWidget(parent), title(title) {

	this->area = BottomPanelTitleArea;
	this->setFixedWidth(width);

	this->layoutWidget = new QWidget(this);
	this->layoutWidget->setGeometry(0, 0, this->width(), this->height() - 27);
}

ShPanelInRibbonTab::~ShPanelInRibbonTab() {

}


void ShPanelInRibbonTab::setPanelTitleArea(PanelTitleArea area) {

	this->area = area;

	if (this->area == BottomPanelTitleArea)
		this->layoutWidget->setGeometry(0, 0, this->width(), this->height() - 27);
	else
		this->layoutWidget->setGeometry(0, 22, this->width(), this->height() - 27);

	this->update();
}

void ShPanelInRibbonTab::addItem(QWidget *widget, const QRect &rect) {

	widget->setParent(this->layoutWidget);
	widget->setGeometry(rect);

}

void ShPanelInRibbonTab::setPanelWidth(int width) {

	this->setFixedWidth(width);
	this->update();
}


void ShPanelInRibbonTab::paintEvent(QPaintEvent *event) {

	QPainter paint(this);

	QFontMetrics fm(paint.font());

	int width = fm.width(this->title);
	int height = fm.height();
	QPoint pos;


	if (this->area == BottomPanelTitleArea) {

		pos = QPoint((this->width() / 2) - (width / 2), this->height() - (height / 2));
		paint.drawText(pos, this->title);
		paint.setPen(QColor(195, 195, 195));
		paint.drawLine(5, this->height() - height - 10, this->width() - 5, this->height() - height - 10);

	}
	else {

		pos = QPoint((this->width() / 2) - (width / 2), height);
		paint.drawText(pos, this->title);
		paint.setPen(QColor(195, 195, 195));
		paint.drawLine(5, height + 5, this->width() - 5, height + 5);


	}
}

#include <QResizeEvent>
void ShPanelInRibbonTab::resizeEvent(QResizeEvent *event) {

	QWidget::resizeEvent(event);

	if (this->area == BottomPanelTitleArea)
		this->layoutWidget->setGeometry(0, 0, event->size().width(), event->size().height() - 27);
	else
		this->layoutWidget->setGeometry(0, 22, event->size().width(), event->size().height() - 27);


}