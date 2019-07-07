
#ifndef _SHMENUBAR_H
#define _SHMENUBAR_H

#include <qmenubar.h>

class ShEmptyDrawingFileMenu;
class ShFileMenu;
class ShEditMenu;
class ShDrawMenu;
class ShModifyMenu;
class ShCAD;
class ShMenuBar : public QMenuBar {

private:
	ShCAD *parent;

public:
	ShMenuBar(ShCAD *parent = nullptr);
	~ShMenuBar();

	void activateMenu();
	void deactivateMenu();

	void newActionClicked();

private:

	ShEmptyDrawingFileMenu *emptyFileMenu;
	ShFileMenu *fileMenu;
	ShEditMenu *editMenu;
	ShDrawMenu *drawMenu;
	ShModifyMenu *modifyMenu;

};

#endif //_SHMENUBAR_H