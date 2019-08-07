
#ifndef _SHMENUBAR_H
#define _SHMENUBAR_H

#include <qmenubar.h>
#include "Chain of Responsibility\ShChain.h"

class ShEmptyDrawingFileMenu;
class ShFileMenu;
class ShEditMenu;
class ShDrawMenu;
class ShModifyMenu;

class ShMenuBar : public QMenuBar, public ShChain {

public:
	ShMenuBar(ShChain *chain, QWidget *parent = nullptr);
	~ShMenuBar();

	void activateMenu();
	void deactivateMenu();

private:

	ShEmptyDrawingFileMenu *emptyFileMenu;
	ShFileMenu *fileMenu;
	ShEditMenu *editMenu;
	ShDrawMenu *drawMenu;
	ShModifyMenu *modifyMenu;

};

#endif //_SHMENUBAR_H