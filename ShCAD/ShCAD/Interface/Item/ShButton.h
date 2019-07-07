
#ifndef _SHBUTTON_H
#define _SHBUTTON_H

#include <qpushbutton.h>

class ShButtonWithMenuPopup : public QWidget {
	Q_OBJECT

protected:
	class ShButton : public QPushButton {
	public:
		bool hoverMovedIn;
		bool hoverStayed;
		ShButton(QWidget *parent = nullptr);
		~ShButton();

	protected:
		void paintEvent(QPaintEvent *event);
	};

	class ShMenuPopupButton : public QPushButton {
	public:
		bool hoverMovedIn;
		bool hoverStayed;
		ShMenuPopupButton(QWidget *parent = nullptr);
		~ShMenuPopupButton();
	protected:
		void paintEvent(QPaintEvent *event);

	};

protected:
	ShButtonWithMenuPopup::ShButton *button;
	ShButtonWithMenuPopup::ShMenuPopupButton *popupButton;


public:
	ShButtonWithMenuPopup(QWidget *parent = nullptr);
	~ShButtonWithMenuPopup();

	void setIcon(const QIcon& icon);
	void setMenu(QMenu *menu);

signals:
	void pressed();

private:
	void buttonClicked();


protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual void leaveEvent(QEvent *event);
};



class ShButton : public QPushButton {

private:
	bool hoverStayed;

public:
	ShButton(QWidget *parent = nullptr);
	~ShButton();

protected:
	virtual void enterEvent(QEvent* event);
	virtual void leaveEvent(QEvent *event);
	virtual void paintEvent(QPaintEvent *event);
};

class StateButton : public QPushButton {
	Q_OBJECT
public:
	bool state;

public:
	StateButton(const QString &text, QWidget *parent = nullptr);
	StateButton(QWidget *parent = nullptr);
	~StateButton();

	void setState(bool on);
	inline bool getState() const { return this->state; }

signals:
	void pressed();

protected:
	void paintEvent(QPaintEvent *event);

	private slots:
	void buttonPressed();
};



#endif //_SHBUTTON_H