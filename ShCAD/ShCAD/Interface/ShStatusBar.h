
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

#ifndef _SHSTATUSBAR_H
#define _SHSTATUSBAR_H

#include <qstatusbar.h>
#include <qpushbutton.h>
class QLabel;
class QAction;
class ShStatusBarButtonChangeableState;
class ShDraftFlag;
class ShStatusBar : public QStatusBar {
	Q_OBJECT


private:
	QLabel *coordinates;
	ShStatusBarButtonChangeableState *orthogonalButton;

public:
	ShStatusBar(QWidget *parent = 0);
	~ShStatusBar();

	void Update(double x, double y, double z, double zoomRate);
	void Update(const ShDraftFlag& draftFlag);
	
	
	private slots:
	void OrthoClicked();
};

class ShStatusBarButtonChangeableState : public QPushButton {

public:
	bool state;

public:
	ShStatusBarButtonChangeableState(const QString &text, QWidget *parent = 0);
	~ShStatusBarButtonChangeableState();

	void SetState(bool on);
	inline bool GetState() const { return this->state; }

protected:
	void paintEvent(QPaintEvent *event);
};


#endif //_SHSTATUSBAR_H