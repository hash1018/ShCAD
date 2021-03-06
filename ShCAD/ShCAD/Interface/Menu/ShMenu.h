
#ifndef _SHMENU_H
#define _SHMENU_H

#include <qmenu.h>
#include "Chain of Responsibility\ShChain.h"

class ShAbstractMenu : public QMenu, public ShChain {

public:
	ShAbstractMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	virtual ~ShAbstractMenu() = 0;

};

class ShEmptyDrawingFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;

public:
	ShEmptyDrawingFileMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShEmptyDrawingFileMenu();

	private slots:
	void newActionClicked();
};

class ShFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;
	QAction *plotAction;
	QAction *previewAction;

public:
	ShFileMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShFileMenu();

	private slots:
	void newActionClicked();
	void plotActionClicked();
	void previewActionClicked();
};

class ShEditMenu : public ShAbstractMenu {

public:
	ShEditMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
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
	ShDrawMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShDrawMenu();

private:
	void createCircleMenu();
	void createArcMenu();

	private slots:
	void lineActionClicked();
	void circleCenterRadiusActionClicked();
	void circleCenterDiameterActionClicked();
	void circleTwoPointActionClicked();
	void circleThreePointActionClicked();

	void arcThreePointActionClicked();

	void arcStartCenterEndActionClicked();
	void arcStartCenterAngleActionClicked();
	void arcStartCenterLengthActionClicked();

	void arcStartEndAngleActionClicked();
	void arcStartEndDirectionActionClicked();
	void arcStartEndRadiusActionClicked();

	void arcCenterStartEndActionClicked();
	void arcCenterStartAngleActionClicked();
	void arcCenterStartLengthActionClicked();
};

class ShModifyMenu : public ShAbstractMenu {

private:
	QAction *eraseAction;
	QAction *copyAction;
	QAction *mirrorAction;
	QAction *offsetAction;
	QAction *moveAction;
	QAction *rotateAction;
	QAction *scaleAction;
	QAction *stretchAction;
	QAction *trimAction;
	QAction *extendAction;

public:
	ShModifyMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShModifyMenu();

	private slots:
	void moveActionClicked();
	void copyActionClicked();
	void mirrorActionClicked();
	void offsetActionClicked();
	void rotateActionClicked();
	void eraseActionClicked();
	void extendActionClicked();
	void trimActionClicked();
	void stretchActionClicked();
};


class ShWindowMenu : public ShAbstractMenu {

private:
	QAction *tabbedViewAction;
	QAction *subWindowViewAction;
	QAction *cascadeAction;
	QAction *tileAction;

public:
	ShWindowMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShWindowMenu();

	private slots:
	void tabbedViewActionClicked();
	void subWindowViewActionClicked();
	void cascadeActionClicked();
	void tileActionClicked();

};

class ShDimMenu : public ShAbstractMenu {

private:
	QAction *dimLinearAcion;
	QAction *dimAlignedAction;
	QAction *dimAngularAction;
	QAction *dimRadiusAction;
	QAction *dimDiameterAction;
	QAction *dimArcLengthAction;

public:
	ShDimMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShDimMenu();

	private slots:
	void dimLinearActionClicked();
	void dimAlignedActionClicked();
	void dimAngularActionClicked();
	void dimRadiusActionClicked();
	void dimDiameterActionClicked();
	void dimArcLengthActionClicked();

};

#endif //_SHMENU_H