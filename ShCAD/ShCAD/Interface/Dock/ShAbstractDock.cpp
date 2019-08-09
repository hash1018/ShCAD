
#include "ShAbstractDock.h"

ShAbstractDock::ShAbstractDock(ShChain *chain, QWidget *parent)
	:ShChain(chain), QDockWidget(parent) {

}

ShAbstractDock::~ShAbstractDock() {

}