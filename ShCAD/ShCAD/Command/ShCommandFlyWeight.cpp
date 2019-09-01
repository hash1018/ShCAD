
#include "ShCommandFlyWeight.h"
#include "ShCommand.h"

ShCommandFlyWeight::ShCommandFlyWeight() {

}

ShCommandFlyWeight::~ShCommandFlyWeight() {

	for (int i = 0; i < this->pool.size(); i++)
		delete this->pool.at(i);
}

void ShCommandFlyWeight::add(ShCommand *command) {

	this->pool.append(command);
}

ShCommand* ShCommandFlyWeight::search(CommandType type) {

	for (int i = 0; i < this->pool.size(); i++) {

		if (this->pool.at(i)->getType() == type)
			return this->pool.at(i);
	}

	return nullptr;
}

////////////////////////////////////////////////////////////

ShCommandFactory ShCommandFactory::instance;

ShCommandFactory::ShCommandFactory() {

}

ShCommandFactory::~ShCommandFactory() {

}

ShCommandFactory* ShCommandFactory::getInstance() {

	return &(ShCommandFactory::instance);
}

ShCommand* ShCommandFactory::get(CommandType type) {

	ShCommand *command = this->flyWeight.search(type);

	if (command == nullptr) {
	
		command = this->create(type);
		this->flyWeight.add(command);
	}

	return command;
}

ShCommand* ShCommandFactory::create(CommandType type) {

	if (type == CommandType::Empty_Cancel)
		return new ShEmptyCancelCommand;
	else if (type == CommandType::AbsoluteCoordinate)
		return new ShAbsoluteCoordinateCommand;
	else if (type == CommandType::RelativeCoordinate)
		return new ShRelativeCoordinateCommand;
	else if (type == CommandType::PolarCoordinate)
		return new ShPolarCoordinateCommand;
	else if (type == CommandType::DistanceFromBase)
		return new ShDistanceFromBaseCommand;
	else if (type == CommandType::AngleFromBase)
		return new ShAngleFromBaseCommand;

	return new ShEmptyCancelCommand;
}