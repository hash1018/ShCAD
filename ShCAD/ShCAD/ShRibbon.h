
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
class QTabWidget;
class ShRibbonTab;
class ShColumnInRibbonTab;
class ShRibbon : public QToolBar {

protected:
	QTabWidget *tab;

public:
	ShRibbon(QWidget *parent = 0);
	ShRibbon(const QSize& size, QWidget *parent = 0);
	ShRibbon(int height, QWidget *parent = 0);
	~ShRibbon();

	ShRibbonTab* AddTab(const QString &title);
	ShRibbonTab* AddTab(ShRibbonTab *tab);

};


class ShRibbonTab: public QToolBar {
	
public:
	ShRibbonTab(QWidget *parent=0);
	ShRibbonTab(const QString& title, QWidget *parent = 0);
	~ShRibbonTab();

public:
	ShColumnInRibbonTab* AddColumn();
	ShColumnInRibbonTab* AddColumn(const QString& columnTitle);

	ShColumnInRibbonTab *AddColumn(const QString& columnTitle, int columnWidth);
	ShColumnInRibbonTab *AddColumn(ShColumnInRibbonTab *column);
	

};

class ShColumnInRibbonTab : public QWidget {
	

public:
	enum ColumnTitleArea {
		TopColumnTitleArea = 0, 
		BottomColumnTitleArea = 1
	};

protected:
	QString title;
	ColumnTitleArea area;
	//child item such as pushButton,listBox.. etc must be within in following widget.
	QWidget *layoutWidget;

	
public:
	ShColumnInRibbonTab(QWidget *parent, const QString& title);
	ShColumnInRibbonTab(QWidget *parent, const QString &title, int width);
	~ShColumnInRibbonTab();
	

	void SetColumnTitleArea(ColumnTitleArea area);
	void AddItem(QWidget *widget, const QRect& rect);
	void SetColumnWidth(int width);



protected:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent *event);

};
#endif //_SHRIBBON_H