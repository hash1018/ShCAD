
#ifndef _SHCOMMANDFLYWEIGHT_H
#define _SHCOMMANDFLYWEIGHT_H

#include <qlist.h>
#include "ShCommandType.h"
class ShCommand;

class ShCommandFlyWeight {
	
	friend class ShCommandFactory;
	
private:
	QList<ShCommand*> pool;

private:
	ShCommandFlyWeight();
	~ShCommandFlyWeight();

	void add(ShCommand *command);
	ShCommand* search(CommandType type);

};

///////////////////////////////////////////

class ShCommandFactory {

private:
	ShCommandFlyWeight flyWeight;

private:
	static ShCommandFactory instance;

	ShCommandFactory();
	~ShCommandFactory();

	ShCommand* create(CommandType type);

public:
	static ShCommandFactory* getInstance();

	ShCommand* get(CommandType type);
};

#endif //_SHCOMMANDFLYWEIGHT_H