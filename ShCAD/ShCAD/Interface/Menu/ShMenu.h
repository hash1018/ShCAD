
#ifndef _ShMENU_H
#define _ShMENU_H

#include <qmenu.h>

class ShMenuBar;
class ShAbstractMenu : public QMenu {

protected:
	ShMenuBar *parent;

public:
	ShAbstractMenu(const QString &title, ShMenuBar *parent = nullptr);
	virtual ~ShAbstractMenu() = 0;

};

class ShEmptyDrawingFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;

public:
	ShEmptyDrawingFileMenu(const QString &title, ShMenuBar *parent = nullptr);
	~ShEmptyDrawingFileMenu();

};

class ShFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;
	QAction *plotAction;
	QAction *previewAction;

public:
	ShFileMenu(const QString &title, ShMenuBar *parent = nullptr);
	~ShFileMenu();
};

class ShEditMenu : public ShAbstractMenu {

public:
	ShEditMenu(const QString &title, ShMenuBar *parent = nullptr);
	~ShEditMenu();

};

class ShDrawMenu : public ShAbstractMenu {

private:
	QAction *lineAction;

	QAction *polyLineAction;
	QAction *polygonAction;
	QAction *rectangleAction;

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
	ShDrawMenu(const QString &title, ShMenuBar *parent = nullptr);
	~ShDrawMenu();

private:
	void createCircleMenu();
	void createArcMenu();
};

class ShModifyMenu : public ShAbstractMenu {

private:
	QAction *eraseAction;
	QAction *copyAction;
	QAction *mirrorAction;
	QAction *moveAction;
	QAction *rotateAction;
	QAction *scaleAction;
	QAction *stretchAction;
	QAction *trimAction;
	QAction *extendAction;

public:
	ShModifyMenu(const QString &title, ShMenuBar *parent = nullptr);
	~ShModifyMenu();

};

#endif _MENU_H