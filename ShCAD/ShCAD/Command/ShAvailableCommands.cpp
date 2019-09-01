
#include "ShAvailableCommands.h"
#include "ShCommand.h"
#include "ShCommandFlyWeight.h"
#include "Manager\ShCommandLogManager.h"
#include "Manager\ShLanguageManager.h"
#include "Command\ShCustomCommand.h"

ShAvailableCommands::ShBuilder::ShBuilder(ShCADWidget *widget, ShActionHandler *actionHandler)
	:widget(widget), actionHandler(actionHandler) {

}

ShAvailableCommands::ShBuilder::~ShBuilder() {

	
}

ShAvailableCommands::ShBuilder& ShAvailableCommands::ShBuilder::addAvailableCommand(CommandType type) {

	if (type == CustomCommand)
		return *this;

	ShCommandFactory *factory = ShCommandFactory::getInstance();
	ShCommand *command = factory->get(type);

	this->list.append(command);
	
	return *this;
}

ShAvailableCommands::ShBuilder& ShAvailableCommands::ShBuilder::addAvailableCommand(ShAbstractCustomCommand *command) {

	this->list.append(command);

	return *this;
}

ShAvailableCommands* ShAvailableCommands::ShBuilder::build() {

	return new ShAvailableCommands(*this);
}


//////////////////////////////////////////////////////

ShAvailableCommands::ShAvailableCommands(const ShAvailableCommands::ShBuilder &builder)
	:widget(builder.widget), actionHandler(builder.actionHandler), list(builder.list) {


}

ShAvailableCommands::~ShAvailableCommands() {

	for (int i = 0; i < this->list.size(); i++) {

		if (dynamic_cast<ShAbstractCustomCommand*>(this->list.at(i)))
			delete this->list.at(i);
	}
}

void ShAvailableCommands::interpret(const QString &command) {

	int i = 0;

	while (i < this->list.size()) {
	
		if (this->list.at(i)->isMatched(command) == true)
			break;

		i++;
	}

	if (i < this->list.size()) {
	
		this->list.at(i)->interpret(widget, actionHandler, command);
		return;
	}

	shCommandLogManager->appendListEditTextWith("");
	shCommandLogManager->appendList(shGetLanValue_command("Command/Unknown command"));
}

void ShAvailableCommands::remove(CommandType type) {

	if (type == CustomCommand)
		return;

	for (int i = 0; i < this->list.size(); i++) {
	
		if (this->list.at(i)->getType() == type) {
			this->list.removeOne(this->list.at(i));
			return;
		}
	}
}

void ShAvailableCommands::add(CommandType type) {

	if (type == CustomCommand)
		return;

	ShCommandFactory *factory = ShCommandFactory::getInstance();
	ShCommand *command = factory->get(type);

	this->list.append(command);

}

void ShAvailableCommands::add(ShAbstractCustomCommand *command) {

	this->list.append(command);
}