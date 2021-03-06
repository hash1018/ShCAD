
#ifndef _SHAVAILABLECOMMANDS_H
#define _SHAVAILABLECOMMANDS_H


//FlyWeight Pattern, Strategy Pattern, FactoryMethod Pattern, Singleton Pattern.

#include <qlist.h>
#include "ShCommandType.h"

class ShCommand;
class ShCADWidget;
class ShActionHandler;
class ShAbstractCustomCommand;

class ShAvailableCommands {

private:
	ShCADWidget *widget;
	ShActionHandler *actionHandler;
	QList<ShCommand*> list;

public:
	
	//Nested class
	class ShBuilder {
		friend class ShAvailableCommands;

	private:
		ShCADWidget *widget;
		ShActionHandler *actionHandler;
		QList<ShCommand*> list;

	public:
		ShBuilder(ShCADWidget *widget, ShActionHandler *actionHandler);
		~ShBuilder();
		ShAvailableCommands::ShBuilder& addAvailableCommand(CommandType type);
		ShAvailableCommands::ShBuilder& addAvailableCommand(ShAbstractCustomCommand *command);
		ShAvailableCommands* build();
	};

public:
	ShAvailableCommands(const ShAvailableCommands::ShBuilder &builder);
	~ShAvailableCommands();

	void interpret(const QString &command);

	void remove(CommandType type);
	void remove(ShAbstractCustomCommand *command);
	void add(CommandType type);
	void add(ShAbstractCustomCommand *command);

};

#endif //_SHAVAILABLECOMMANDS_H