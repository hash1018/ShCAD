
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


#include "ShRibbonMenu.h"


ShRibbonMenu::ShRibbonMenu(int height, QWidget *parent)
	:ShRibbon(height, parent) {

	this->homeTab = new ShHomeTab("Home", this);
	this->AddTab(this->homeTab);

	this->insertTab = new ShInsertTab("Insert", this);
	this->AddTab(this->insertTab);

	this->annotateTab = new ShAnnotateTab("Annotate", this);
	this->AddTab(this->annotateTab);

	this->parametricTab = new ShParametricTab("Parametric", this);
	this->AddTab(this->parametricTab);

	this->viewTab = new ShViewTab("View", this);
	this->AddTab(this->viewTab);

	this->manageTab = new ShManageTab("Manage", this);
	this->AddTab(this->manageTab);

}

ShRibbonMenu::~ShRibbonMenu() {


}


///////////////////////////////////////////////////////////////////////////////////

#include "ShDrawInterface.h"
ShHomeTab::ShHomeTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

	this->drawColumn = new ShDrawColumn(this, "Draw", 100);
	this->AddColumn(this->drawColumn);
}

ShHomeTab::~ShHomeTab() {

}


////////////////////////////////////////////////////////////////////////////////////

ShInsertTab::ShInsertTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShInsertTab::~ShInsertTab() {

}

/////////////////////////////////////////////////////////////////////////////////////////

ShAnnotateTab::ShAnnotateTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShAnnotateTab::~ShAnnotateTab() {

}


//////////////////////////////////////////////////////////////////////////////////////////

ShParametricTab::ShParametricTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShParametricTab::~ShParametricTab() {

}


///////////////////////////////////////////////////////////////////////////////////////////

ShViewTab::ShViewTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShViewTab::~ShViewTab() {

}

///////////////////////////////////////////////////////////////////////////////////////////

ShManageTab::ShManageTab(const QString &title, QWidget *parent)
	:ShRibbonTab(title, parent) {

}

ShManageTab::~ShManageTab() {

}

/////////////////////////////////////////////////////////////////////////////////////////////