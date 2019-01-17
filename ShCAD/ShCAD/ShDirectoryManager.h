

#ifndef _SHDIRECTORYMANAGER_H
#define _SHDIRECTORYMANAGER_H

#include <qstring.h>
class ShDirectoryManager {

public:
	ShDirectoryManager();
	~ShDirectoryManager();

	static QString GetCurrentPath();
	static QString GetImageUiPath();
};


#endif //_SHDIRECTORYMANAGER_H