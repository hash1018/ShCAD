
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


#ifndef _SHRIBBON_H
#define _SHRIBBON_H

#include <qtoolbar.h>
#include "Chain of Responsibility\ShChain.h"

class QTabWidget;
class ShRibbonTab;
class ShPanelInRibbonTab;
class ShRibbon : public QToolBar, public ShChain  {

protected:
	QTabWidget *tab;

public:
	ShRibbon(ShChain *chain, QWidget *parent = nullptr);
	ShRibbon(ShChain *chain, const QSize& size, QWidget *parent = nullptr);
	ShRibbon(ShChain *chain, int height, QWidget *parent = nullptr);
	~ShRibbon();

	ShRibbonTab* addTab(const QString &title);
	ShRibbonTab* addTab(ShRibbonTab *tab);

};


class ShRibbonTab : public QToolBar, public ShChain {

public:
	ShRibbonTab(ShChain *chain, QWidget *parent = nullptr);
	ShRibbonTab(const QString& title, ShChain *chain, QWidget *parent = nullptr);
	~ShRibbonTab();

public:
	ShPanelInRibbonTab* addPanel();
	ShPanelInRibbonTab* addPanel(const QString& panelTitle);

	ShPanelInRibbonTab *addPanel(const QString& panelTitle, int panelWidth);
	ShPanelInRibbonTab *addPanel(ShPanelInRibbonTab *panel);


};

class ShPanelInRibbonTab : public QWidget, public ShChain {

public:
	enum PanelTitleArea {
		TopPanelTitleArea = 0,
		BottomPanelTitleArea = 1
	};

protected:
	QString title;
	PanelTitleArea area;
	//child item such as pushButton,listBox.. etc must be within in following widget.
	QWidget *layoutWidget;


public:
	ShPanelInRibbonTab(ShChain *chain, QWidget *parent, const QString& title);
	ShPanelInRibbonTab(ShChain *chain, QWidget *parent, const QString &title, int width);
	~ShPanelInRibbonTab();


	void setPanelTitleArea(PanelTitleArea area);
	void addItem(QWidget *widget, const QRect& rect);
	void setPanelWidth(int width);



protected:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent *event);

};
#endif //_SHRIBBON_H