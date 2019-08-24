
#ifndef _SHKEYFLYWEIGHT_H
#define _SHKEYFLYWEIGHT_H

#include <qlist.h>
#include "ShKeyType.h"
class ShKey;

class ShKeyFlyWeight {
	friend class ShKeyFactory;
private:
	QList<ShKey*> pool;

private:
	ShKeyFlyWeight();
	~ShKeyFlyWeight();

	void add(ShKey *key);
	ShKey* search(KeyType keyType);

};

class ShKeyFactory {

private:
	ShKeyFlyWeight flyWeight;

private:
	static ShKeyFactory instance;

	ShKeyFactory();
	~ShKeyFactory();

	ShKey* create(KeyType keyType);

public:
	static ShKeyFactory* getInstance();

	ShKey* get(KeyType keyType);

};


#endif //_SHKEYFLYWEIGHT_H