
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
	bool operator==(const ShKey &other);
	bool compare(const Qt::Key &key, const Qt::KeyboardModifiers &modifier);
	ShKey& operator=(const ShKey &other);

	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler) = 0;
	KeyType getKeyType();
};

class ShEscKey : public ShKey {

public:
	ShEscKey(KeyType keyType);
	~ShEscKey();
	bool operator==(const ShEscKey &other);
	ShEscKey& operator=(const ShEscKey &other);

	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);

};


class ShEnterKey : public ShKey {

public:
	ShEnterKey();
	~ShEnterKey();
	bool operator==(const ShEnterKey &other);
	ShEnterKey& operator=(const ShEnterKey &other);

	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);

};

class ShReturnKey : public ShKey {

public:
	ShReturnKey();
	~ShReturnKey();
	bool operator==(const ShReturnKey &other);
	ShReturnKey& operator=(const ShReturnKey &other);
		
	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);
};

#endif //_SHKEY_H