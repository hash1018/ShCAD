
#ifndef _SHCOMMANDLOGMANAGER_H
#define _SHCOMMANDLOGMANAGER_H

#include <qstring.h>
#include "Base\ShSingleton.h"

#define shCommandLogManager ShCommandLogManager::getInstance()

class ShCommandDock;
class ShCommandLogManager {

	DeclareSingleton(ShCommandLogManager)

private:
	ShCommandDock *commandDock;

public:
	void registerInterface(ShCommandDock *commandDock) { this->commandDock = commandDock; }

public:
	void appendHeadTitle(const QString &headTitle);
	void replaceHeadTitle(const QString &headTitle);
	void appendList(const QString &text);
	void appendListEditTextWith(const QString &text);
	void appendListEditTextAndNewLineWith(const QString &text);
	
public:
	QString getEditText();
	QString getHeadTitle();
};

#endif //_SHCOMMANDLOGMANAGER_H