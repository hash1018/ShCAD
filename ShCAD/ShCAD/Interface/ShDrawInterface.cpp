

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

#include "ShDrawInterface.h"
#include "ShDirectoryManager.h"
#include <qpixmap.h>
#include <qbitmap.h>
#include <qmenu.h>

ShDrawColumn::ShDrawColumn(QWidget *parent, const QString &title, int width)
	:ShColumnInRibbonTab(parent, title, width) {
	
	

	this->InitLineButton();
	this->InitCircleButton();
	this->InitArcButton();

	

	

	
	
}

ShDrawColumn::~ShDrawColumn() {


}

void ShDrawColumn::resizeEvent(QResizeEvent *event) {

	ShColumnInRibbonTab::resizeEvent(event);

	int width = this->layoutWidget->width();
	int height = this->layoutWidget->height();

	this->lineButton->setGeometry(0, 0, width / 2, height / 3);
	this->circleButton->setGeometry(width / 2, 0, width / 2, height / 3);

	this->arcButton->setGeometry(0, height / 3, width / 2, height / 3);

}



#include "Singleton Pattern\ShWidgetManager.h"
#include "ShGraphicView.h"
void ShDrawColumn::LineButtonClicked() {
	qDebug("LineButtonClicked");

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget"); 
		return;
	}
	
	
	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(ActionType::ActionDrawLine);
	
	
}

void ShDrawColumn::CircleButtonClicked() {
	qDebug("CircleButtonClicked");

	if (ShWidgetManager::GetInstance()->GetActivatedWidget() == 0) {
		qDebug("no activated widget");
		return;
	}

	ShWidgetManager::GetInstance()->GetActivatedWidget()->ChangeCurrentAction(ActionType::ActionDefault);

}

void ShDrawColumn::ArcButtonClicked() {


}



void ShDrawColumn::InitLineButton() {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Line.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);


	QIcon icon(pix);
	this->lineButton = new ShButtonWithMenuPopup(this->layoutWidget);
	this->lineButton->SetIcon(icon);

	QMenu *menu = new QMenu(this->lineButton);
	menu->addAction("sdsad");
	menu->addAction("kkkk");
	this->lineButton->SetMenu(menu);




	connect(this->lineButton, &ShButtonWithMenuPopup::pressed, this, &ShDrawColumn::LineButtonClicked);

}

void ShDrawColumn::InitCircleButton() {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Circle.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);
	this->circleButton = new ShButtonWithMenuPopup(this->layoutWidget);
	this->circleButton->SetIcon(icon);

	QMenu *menu = new QMenu(this->circleButton);
	menu->addAction("sdsad");
	menu->addAction("kkkk");
	this->circleButton->SetMenu(menu);


	connect(this->circleButton, &ShButtonWithMenuPopup::pressed, this, &ShDrawColumn::CircleButtonClicked);
}

void ShDrawColumn::InitArcButton() {

	QString path = ShDirectoryManager::GetImageUiPath();

	QPixmap pix(path + "\\Arc.png");
	QBitmap mask = pix.createMaskFromColor(QColor(255, 255, 255), Qt::MaskMode::MaskInColor);
	pix.setMask(mask);

	QIcon icon(pix);
	this->arcButton = new ShButtonWithMenuPopup(this->layoutWidget);
	this->arcButton->SetIcon(icon);

	QMenu *menu = new QMenu(this->arcButton);
	menu->addAction("sdsad");
	menu->addAction("kkkk");
	this->arcButton->SetMenu(menu);


	connect(this->arcButton, &ShButtonWithMenuPopup::pressed, this, &ShDrawColumn::ArcButtonClicked);
}