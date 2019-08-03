
#ifndef _SHBUTTON_H
#define _SHBUTTON_H

#include <qpushbutton.h>
#include <qstring.h>

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

/////////////////////////////////////////////////////////////////


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


//////////////////////////////////////////////////////////////////

class ShButtonWithText : public QWidget {
	Q_OBJECT

public:
	enum TextDirection {
		East,
		West,
		South,
		North,
	};


protected:
	class ShButton : public QPushButton {

	public:
		TextDirection direction;
		bool hoverStayed;
		ShButton(QWidget *parent = nullptr);
		~ShButton();

	protected:
		void paintEvent(QPaintEvent *event);
	};

	class ShTextButton : public QPushButton {

	public:
		TextDirection direction;
		bool hoverStayed;
		ShTextButton(QWidget *parent = nullptr);
		~ShTextButton();
	protected:
		void paintEvent(QPaintEvent *event);

	};

protected:
	ShButtonWithText::ShButton *button;
	ShButtonWithText::ShTextButton *textButton;
	TextDirection direction;
	int rate;

public:
	ShButtonWithText(QWidget *parent = nullptr);
	~ShButtonWithText();

	void setIcon(const QIcon& icon);
	void setText(const QString &text);
	void setTextDirection(const TextDirection &direction);
	void setIconSize(const QSize &size);

	//Not used yet.
	void setIconSizeRate(int rate); 

signals:
	void pressed();

private:
	void buttonClicked();


protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual void leaveEvent(QEvent *event);
	
};

//////////////////////////////////////////////////////////////////

class ShButtonWithMenuPopupWithText : public QWidget {
	Q_OBJECT

public:
	enum TextDirection {
		East,
		West,
		South,
		North,
	};

protected:
	class ShButton : public QPushButton {

	public:
		TextDirection direction;
		bool hoverMovedIn;
		bool hoverStayed;
		ShButton(QWidget *parent = nullptr);
		~ShButton();

	protected:
		void paintEvent(QPaintEvent *event);
	};

	class ShMenuPopupButton : public QPushButton {

	public:
		TextDirection direction;
		bool hoverMovedIn;
		bool hoverStayed;
		ShMenuPopupButton(QWidget *parent = nullptr);
		~ShMenuPopupButton();
	protected:
		void paintEvent(QPaintEvent *event);

	};

protected:
	ShButtonWithMenuPopupWithText::ShButton *button;
	ShButtonWithMenuPopupWithText::ShMenuPopupButton *popupButton;
	TextDirection direction;

public:
	ShButtonWithMenuPopupWithText(QWidget *parent = nullptr);
	~ShButtonWithMenuPopupWithText();

	void setIcon(const QIcon& icon);
	void setMenu(QMenu *menu);
	void setTextDirection(const TextDirection &direction);
	void setText(const QString &text);
	void setIconSize(const QSize &size);

signals:
	void pressed();

private:
	void buttonClicked();


protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);
	virtual void leaveEvent(QEvent *event);
};


//////////////////////////////////////////////////////////////////



class ShStateButton : public QPushButton {
	Q_OBJECT
public:
	bool state;

public:
	ShStateButton(const QString &text, QWidget *parent = nullptr);
	ShStateButton(QWidget *parent = nullptr);
	~ShStateButton();

	void setState(bool on);
	inline bool getState() const { return this->state; }

signals:
	void pressed();

protected:
	void paintEvent(QPaintEvent *event);

	private slots:
	void buttonPressed();
};


////////////////////////////////////////////////////////////




#endif //_SHBUTTON_H