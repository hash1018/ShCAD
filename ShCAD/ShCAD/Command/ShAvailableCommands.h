
#ifndef _SHAVAILABLECOMMANDS_H
#define _SHAVAILABLECOMMANDS_H

#include <qlist.h>
#include "ShCommandType.h"

class ShCommand;
class ShCADWidget;
class ShActionHandler;

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

		ShAvailableCommands* build();
	};

public:
	ShAvailableCommands(const ShAvailableCommands::ShBuilder &builder);
	~ShAvailableCommands();

	void interpret(const QString &command);

};

#endif //_SHAVAILABLECOMMANDS_H