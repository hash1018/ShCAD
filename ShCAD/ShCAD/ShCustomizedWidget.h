

#ifndef _SHCUSTOMIZEDWIDGET_H
#define _SHCUSTOMIZEDWIDGET_H

#include <qpushbutton.h>
class ShButtonWithMenuPopup : public QWidget {
	Q_OBJECT

private:	
	class ShButton : public QPushButton {
	public:
		bool hoverMovedIn;
		ShButton(QWidget *parent = 0);
		~ShButton();

	protected:
		void paintEvent(QPaintEvent *event);
	};

	class ShMenuPopupButton : public QPushButton {
	public:
		bool hoverMovedIn;
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
	void resizeEvent(QResizeEvent *event);
	bool eventFilter(QObject *obj, QEvent *event);
};

#endif //_SHCUSTOMIZEDWIDGET_H