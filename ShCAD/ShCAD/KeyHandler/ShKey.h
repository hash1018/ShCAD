
#ifndef _SHKEY_H
#define _SHKEY_H

#include <qnamespace.h>
#include "ShKeyType.h"
class ShActionHandler;
class ShCADWidget;

class ShKey {
	
protected:
	Qt::Key key;
	Qt::KeyboardModifiers modifier;
	KeyType keyType;

public:
	ShKey(KeyType keyType, const Qt::Key &key, const Qt::KeyboardModifiers &modifier = Qt::NoModifier);
	virtual ~ShKey() = 0;
	
	bool compare(const Qt::Key &key, const Qt::KeyboardModifiers &modifier);
	
	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler) = 0;
	KeyType getKeyType();
};

class ShEscKey : public ShKey {

public:
	ShEscKey(KeyType keyType);
	~ShEscKey();
	
	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);
};


class ShEnterKey : public ShKey {

public:
	ShEnterKey();
	~ShEnterKey();

	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);
};

class ShReturnKey : public ShKey {

public:
	ShReturnKey();
	~ShReturnKey();
	
	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);
};

class ShCtrlZKey : public ShKey {

public:
	ShCtrlZKey();
	~ShCtrlZKey();
	
	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);
};

class ShCtrlYKey : public ShKey {

public:
	ShCtrlYKey();
	~ShCtrlYKey();

	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);
};

class ShCtrlAKey : public ShKey {
	
public:
	ShCtrlAKey();
	~ShCtrlAKey();

	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);

};

#endif //_SHKEY_H