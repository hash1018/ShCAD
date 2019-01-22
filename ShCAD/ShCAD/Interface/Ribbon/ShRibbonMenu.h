
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


#ifndef _SHRIBBONMENU_H
#define _SHRIBBONMENU_H


#include "ShRibbon.h"

class ShHomeTab;
class ShInsertTab;
class ShAnnotateTab;
class ShParametricTab;
class ShViewTab;
class ShManageTab;
class ShRibbonMenu : public ShRibbon {

private:
	ShHomeTab *homeTab;
	ShInsertTab *insertTab;
	ShAnnotateTab *annotateTab;
	ShParametricTab *parametricTab;
	ShViewTab *viewTab;
	ShManageTab *manageTab;

public:
	ShRibbonMenu(int height, QWidget *parent = 0);
	~ShRibbonMenu();

};



class ShInsertTab : public ShRibbonTab {

public:
	ShInsertTab(const QString &title, QWidget *parent = 0);
	~ShInsertTab();

};

class ShAnnotateTab : public ShRibbonTab {

public:
	ShAnnotateTab(const QString &title, QWidget *parent = 0);
	~ShAnnotateTab();

};

class ShParametricTab : public ShRibbonTab {

public:
	ShParametricTab(const QString &title, QWidget *parent = 0);
	~ShParametricTab();

};

class ShViewTab : public ShRibbonTab {

public:
	ShViewTab(const QString &title, QWidget *parent = 0);
	~ShViewTab();

};

class ShManageTab : public ShRibbonTab {

public:
	ShManageTab(const QString &title, QWidget *parent = 0);
	~ShManageTab();

};

#endif //_SHRIBBONMENU_H