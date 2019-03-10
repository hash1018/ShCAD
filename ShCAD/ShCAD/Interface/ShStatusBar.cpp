
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

#include "ShStatusBar.h"
#include <qlabel.h>
#include "Singleton Pattern\ShWidgetManager.h"
#include "Interface\ShGraphicView.h"
ShStatusBar::ShStatusBar(QWidget *parent)
	:QStatusBar(parent) {

	this->coordinates = new QLabel("Coordinates", this);
	this->coordinates->setFixedWidth(200);
	this->addWidget(this->coordinates);

	this->orthogonalButton = new ShStatusBarButtonChangeableState("ortho", this);
	this->orthogonalButton->setShortcut(QKeySequence(Qt::Key::Key_F8));

	this->addWidget(this->orthogonalButton);
	

	connect(this->orthogonalButton, SIGNAL(pressed()), this, SLOT(OrthoClicked()));

}

ShStatusBar::~ShStatusBar() {


}

void ShStatusBar::Update(double x, double y, double z, double zoomRate) {

	QString str = QString::number(x, 'f', 4) + ", " + QString::number(y, 'f', 4) + ", " + QString::number(z, 'd', 0) + ",  " + QString::number(zoomRate, 'f', 2);
	this->coordinates->setText(str);

}

void ShStatusBar::Update(const ShDraftFlag& draftFlag) {

	this->orthogonalButton->SetState(draftFlag.AcceptOrthogonal());

}


void ShStatusBar::OrthoClicked() {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == 0)
		return;
	
	manager->GetActivatedWidget()->SetOrthogonalMode();

	bool state = manager->GetActivatedWidget()->GetDraftFlag().AcceptOrthogonal();

	this->orthogonalButton->SetState(state);
	
}



//////////////////////////////////////////////////////////////////////////

ShStatusBarButtonChangeableState::ShStatusBarButtonChangeableState(const QString &text, QWidget *parent)
	:QPushButton(text, parent), state(false) {

}

ShStatusBarButtonChangeableState::~ShStatusBarButtonChangeableState() {

}

void ShStatusBarButtonChangeableState::SetState(bool on) {

	this->state = on;
	this->update();
}

#include <qpainter.h>
void ShStatusBarButtonChangeableState::paintEvent(QPaintEvent *event) {

	QPushButton::paintEvent(event);

	if (state == false)
		return;

	QPainter painter(this);
	painter.fillRect(0, 0, this->width(), this->height(), QColor(000, 153, 255, 125));
}