
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

#ifndef _SHCUSTOMIZEDWIDGET_H
#define _SHCUSTOMIZEDWIDGET_H

#include <qpushbutton.h>
class ShButtonWithMenuPopup : public QWidget {
	Q_OBJECT

private:
	class ShButton : public QPushButton {
	public:
		bool hoverMovedIn;
		bool hoverStayed;
		ShButton(QWidget *parent = 0);
		~ShButton();

	protected:
		void paintEvent(QPaintEvent *event);
	};

	class ShMenuPopupButton : public QPushButton {
	public:
		bool hoverMovedIn;
		bool hoverStayed;
		ShMenuPopupButton(QWidget *parent = 0);
		~ShMenuPopupButton();
	protected:
		void paintEvent(QPaintEvent *event);

	};

private:
	ShButtonWithMenuPopup::ShButton *button;
	ShButtonWithMenuPopup::ShMenuPopupButton *popupButton;


public:
	ShButtonWithMenuPopup(QWidget *parent = 0);
	~ShButtonWithMenuPopup();

	void SetIcon(const QIcon& icon);
	void SetMenu(QMenu *menu);

signals:
	void pressed();

private:
	void ButtonClicked();

protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual void leaveEvent(QEvent *event);
};



class ShButton : public QPushButton {

private:
	bool hoverStayed;

public:
	ShButton(QWidget *parent = 0);
	~ShButton();

protected:
	virtual void enterEvent(QEvent* event);
	virtual void leaveEvent(QEvent *event);
	virtual void paintEvent(QPaintEvent *event);
};

#endif //_SHCUSTOMIZEDWIDGET_H