
#include "ShCommand.h"
#include "ActionHandler\ShActionHandler.h"
#include <qstring.h>
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Base\ShMath.h"

ShCommand::ShCommand(CommandType type)
	:type(type) {

}

ShCommand::~ShCommand() {

}

void ShCommand::trigger(const ShPoint3d &point,ShActionHandler *actionHandler) {

	actionHandler->trigger(point);
}

bool ShCommand::isNumber(const QString &string) {

	if (string.count('.') > 1)
		return false;
	
	int i = 0;
	int count = string.length();

	for (i = 0; i < count; i++) {

		if (i == 0 && string[i] == '-')
			continue;
		if (string[i] == '.')
			continue;
		if (string[i] >= '0' && string[i] <= '9')
			continue;
		else
			break;
	}

	if (i == count)
		return true;

	return false;
}


//////////////////////////////////////////////////////////

ShEmptyCancelCommand::ShEmptyCancelCommand()
	:ShCommand(CommandType::Empty_Cancel) {

}

ShEmptyCancelCommand::~ShEmptyCancelCommand() {

}

void ShEmptyCancelCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	ShChangeDefaultAfterCancelingCurrentStrategy strategy;
	widget->changeAction(strategy);
}

bool ShEmptyCancelCommand::isMatched(const QString &command) {

	if (command.isEmpty() == true)
		return true;

	return false;
}


//////////////////////////////////////////////////////////////

ShAbsoluteCoordinateCommand::ShAbsoluteCoordinateCommand()
	:ShCommand(CommandType::AbsoluteCoordinate) {

}

ShAbsoluteCoordinateCommand::~ShAbsoluteCoordinateCommand() {

}

void ShAbsoluteCoordinateCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	ShPoint3d point;
	this->convertCoordinate(command, point.x, point.y);

	this->trigger(point, actionHandler);
}

bool ShAbsoluteCoordinateCommand::isMatched(const QString &command) {

	QString x, y, temp;

	if (command.count(',') != 1)
		return false;

	x = command.section(',', 0, 0);
	y = command.section(',', 1, 1);
	temp = command.section(',', 2, 2);

	if (x.length() == 0)
		return false;
	if (y.length() == 0)
		return false;
	if (temp.length() != 0)
		return false;

	if (this->isNumber(x) == false)
		return false;
	if (this->isNumber(y) == false)
		return false;

	return true;
}

void ShAbsoluteCoordinateCommand::convertCoordinate(const QString &command, double &x, double &y) {

	x = command.section(',', 0, 0).toDouble();
	y = command.section(',', 1, 1).toDouble();
}

//////////////////////////////////////////////////////////////////////

ShRelativeCoordinateCommand::ShRelativeCoordinateCommand()
	:ShCommand(CommandType::RelativeCoordinate) {

}

ShRelativeCoordinateCommand::~ShRelativeCoordinateCommand() {

}

void ShRelativeCoordinateCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	ShPoint3d point;
	this->convertCoordinate(command, point.x, point.y);

	ShPoint3d lastBasePoint = actionHandler->getLastBasePoint();

	point.x += lastBasePoint.x;
	point.y += lastBasePoint.y;

	this->trigger(point, actionHandler);
}

bool ShRelativeCoordinateCommand::isMatched(const QString &command) {

	QString x, y, temp;

	if (command.count(',') != 1)
		return false;

	x = command.section(',', 0, 0);
	y = command.section(',', 1, 1);
	temp = command.section(',', 2, 2);

	if (x.length() == 0)
		return false;
	if (y.length() == 0)
		return false;
	if (temp.length() != 0)
		return false;

	temp = x.section('@', 0, 0);
	if (temp.length() != 0)
		return false;

	temp = x.section('@', 2, 2);
	if (temp.length() != 0)
		return false;

	temp = x.section('@', 1, 1);
	if (this->isNumber(temp) == false)
		return false;
	if (this->isNumber(y) == false)
		return false;

	return true;
}

void ShRelativeCoordinateCommand::convertCoordinate(const QString &command, double &x, double &y) {

	QString tempX;
	tempX = command.section(',', 0, 0);
	
	x = tempX.section('@', 1, 1).toDouble();
	y = command.section(',', 1, 1).toDouble();
}

//////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////

ShPolarCoordinateCommand::ShPolarCoordinateCommand()
	:ShCommand(CommandType::PolarCoordinate) {

}

ShPolarCoordinateCommand::~ShPolarCoordinateCommand() {

}

void ShPolarCoordinateCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	double angle, length;
	this->convertCoordinate(command, angle, length);

	ShPoint3d point = actionHandler->getLastBasePoint();

	math::rotate(angle, point.x, point.y, point.x + length, point.y, point.x, point.y);
	this->trigger(point, actionHandler);
}

bool ShPolarCoordinateCommand::isMatched(const QString &command) {

	if (command.count('<') != 1)
		return false;

	QString length, angle, temp;

	length = command.section('<', 0, 0); 
	angle = command.section('<', 1, 1);
	temp = command.section('<', 2, 2);

	if (length.length() == 0)
		return false;
	if (angle.length() == 0)
		return false;
	if (temp.length() != 0)
		return false;

	temp = length.section('@', 0, 0);
	if (temp.length() != 0)
		return false;

	temp = length.section('@', 1, 1);
	if (temp.length() == 0)
		return false;

	if (this->isNumber(temp) == false)
		return false;
	if (this->isNumber(angle) == false)
		return false;

	return true;
}

void ShPolarCoordinateCommand::convertCoordinate(const QString &command, double &angle, double &length) {

	angle = command.section('<', 1, 1).toDouble();
	length = command.section('<', 0, 0).section('@', 1, 1).toDouble();
}

/////////////////////////////////////////////////////////////////////////
