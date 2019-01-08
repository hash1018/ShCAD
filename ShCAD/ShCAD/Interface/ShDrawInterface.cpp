

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

ShDrawColumn::ShDrawColumn(QWidget *parent, const QString &title, int width)
	:ShColumnInRibbonTab(parent, title, width) {

	this->lineButton = new QToolButton(this->layoutWidget);
	this->lineButton->setText("Line");
	//this->lineButton->setStyleSheet("background:transparent"); it worked.

	this->circleButton = new QToolButton(this->layoutWidget);
	this->circleButton->setText("Circle");

	this->arcButton = new QToolButton(this->layoutWidget);
	this->arcButton->setText("Arc");

	connect(this->lineButton, &QToolButton::pressed, this, &ShDrawColumn::LineButtonClicked);
}

ShDrawColumn::~ShDrawColumn() {


}

void ShDrawColumn::resizeEvent(QResizeEvent *event) {

	ShColumnInRibbonTab::resizeEvent(event);

	int width = this->layoutWidget->width();
	int height = this->layoutWidget->height();

	this->lineButton->setGeometry(0, 0, width / 3, height);
	this->circleButton->setGeometry(width / 3, 0, width / 3, height);
	this->arcButton->setGeometry(width / 3 * 2, 0, width / 3, height);

}

#include <qmessagebox.h>
void ShDrawColumn::LineButtonClicked() {
	QMessageBox box;
	box.setText("line clicked");
	box.exec();
}

void ShDrawColumn::CircleButtonClicked() {

}

void ShDrawColumn::ArcButtonClicked() {


}