
#ifndef _SHCHANGEMANAGER_H
#define _SHCHANGEMANAGER_H

// Mediator Pattern, Singleton Pattern, Observer Pattern.

#include "Base\ShSingleton.h"
#include <qlist.h>

class ShNotifyEvent;
class ShCADWidget;
class ShObserver;

class ShChangeManager {

	DeclareSingleton(ShChangeManager)

public:
	void registerObserver(ShObserver *observer);
	void notify(ShCADWidget *widget, ShNotifyEvent *event);
	

private:
	QList<ShObserver*> observers;
};

#endif //_SHCHANGEMANAGER_H