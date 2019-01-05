

#ifndef _SHMENUBAR_H
#define _SHMENUBAR_H

#include <qmenubar.h>

class ShFileMenu;
class ShMenuBar : public QMenuBar {


public:
	ShMenuBar(QWidget *parent = 0);
	~ShMenuBar();


private:
	ShFileMenu *fileMenu;
};


class ShFileMenu : public QMenu {

private:
	QAction *newAction;

public:
	ShFileMenu(const QString &title, QWidget *parent = 0);
	~ShFileMenu();

};

#endif //_SHMENUBAR_H