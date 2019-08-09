
#ifndef _SHABSTRACTDOCK_H
#define _SHABSTRACTDOCK_H

#include "Chain of Responsibility\ShChain.h"
#include <qdockwidget.h>

class ShAbstractDock : public QDockWidget, public ShChain {

public:
	ShAbstractDock(ShChain *chain, QWidget *parent = nullptr);
	~ShAbstractDock();


};

#endif //_SHABSTRACTDOCK_H