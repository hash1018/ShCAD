

#ifndef _SHMENU_H
#define _SHMENU_H

#include <qmenu.h>

class ShAbstractMenu : public QMenu {

public:
	ShAbstractMenu(const QString &title, QWidget *parent = 0);
	virtual ~ShAbstractMenu() = 0;

protected:
	QIcon GetIcon(const QString &filePath);
};

class ShEmptyDrawingFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;

public:
	ShEmptyDrawingFileMenu(const QString &title, QWidget *parent = 0);
	~ShEmptyDrawingFileMenu();

};


class ShFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;

public:
	ShFileMenu(const QString &title, QWidget *parent = 0);
	~ShFileMenu();

};

class ShDrawMenu : public ShAbstractMenu {

private:
	QAction *lineAction;

	QMenu *circleMenu;
	QAction *circleCenterRadiusAction;
	QAction *circleCenterDiameterAction;
	QAction *circleTwoPointAction;
	QAction *circleThreePointAction;

	QMenu *arcMenu;
	QAction *arcThreePointAction;
	QAction *arcStartCenterEndAction;
	QAction *arcStartCenterAngleAction;
	QAction *arcStartCenterLengthAction;
	QAction *arcStartEndAngleAction;
	QAction *arcStartEndDirectionAction;
	QAction *arcStartEndRadiusAction;
	QAction *arcCenterStartEndAction;
	QAction *arcCenterStartAngleAction;
	QAction *arcCenterStartLengthAction;

public:
	ShDrawMenu(const QString &title, QWidget *parent = 0);
	~ShDrawMenu();



private:
	void CreateCircleMenu();
	void CreateArcMenu();

	private slots:
	void LineActionClicked();

	void CircleCenterRadiusClicked();
	void CircleCenterDiameterClicked();

	void CircleTwoPointClicked();
	void CircleThreePointClicked();

	void ArcThreePointClicked();

	void ArcStartCenterEndClicked();
	void ArcStartCenterAngleClicked();
	void ArcStartCenterLengthClicked();

	void ArcStartEndAngleClicked();
	void ArcStartEndDirectionClicked();
	void ArcStartEndRadiusClicked();

	void ArcCenterStartEndClicked();
	void ArcCenterStartAngleClicked();
	void ArcCenterStartLengthClicked();
};



#endif //_SHMENU_H