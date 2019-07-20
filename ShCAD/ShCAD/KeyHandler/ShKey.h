
#ifndef _SHKEY_H
#define _SHKEY_H

#include <qnamespace.h>

class ShKey {
	
protected:
	Qt::Key key;
	Qt::KeyboardModifiers modifier;

public:
	ShKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier = Qt::NoModifier);
	virtual ~ShKey() = 0;
	bool operator==(const ShKey &other);
	bool compare(const Qt::Key &key, const Qt::KeyboardModifiers &modifier);
	ShKey& operator=(const ShKey &other);

	virtual void press() = 0;
};

class ShEscKey : public ShKey {

public:
	ShEscKey();
	~ShEscKey();
	bool operator==(const ShEscKey &other);
	ShEscKey& operator=(const ShEscKey &other);

	virtual void press();

};

class ShEnterKey : public ShKey {

public:
	ShEnterKey();
	~ShEnterKey();
	bool operator==(const ShEnterKey &other);
	ShEnterKey& operator=(const ShEnterKey &other);

	virtual void press();

};

class ShReturnKey : public ShKey {

public:
	ShReturnKey();
	~ShReturnKey();
	bool operator==(const ShReturnKey &other);
	ShReturnKey& operator=(const ShReturnKey &other);
		
	virtual void press();
};

#endif //_SHKEY_H