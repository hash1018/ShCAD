
#ifndef _SHCOMMAND_H
#define _SHCOMMAND_H

#include "ShCommandType.h"

class ShCADWidget;
class ShActionHandler;
class QString;
class ShPoint3d;

class ShCommand {

protected:
	CommandType type;

public:
	ShCommand(CommandType type);
	virtual ~ShCommand() = 0;

public:
	virtual void interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) = 0;
	virtual bool isMatched(const QString &command) = 0;
	inline CommandType getType() const { return this->type; }

protected:
	void trigger(const ShPoint3d &point, ShActionHandler *actionHandler);
	bool isNumber(const QString &string);
};

/////////////////////////////////////////////////////

class ShEmptyCancelCommand : public ShCommand {

public:
	ShEmptyCancelCommand();
	~ShEmptyCancelCommand();

public:
	virtual void interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command);
	virtual bool isMatched(const QString &command);
	
};

//////////////////////////////////////////////////////

class ShAbsoluteCoordinateCommand : public ShCommand {

public:
	ShAbsoluteCoordinateCommand();
	~ShAbsoluteCoordinateCommand();

public:
	virtual void interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command);
	virtual bool isMatched(const QString &command);
	
private:
	void convertCoordinate(const QString &command, double &x, double &y);
};

class ShRelativeCoordinateCommand : public ShCommand {

public:
	ShRelativeCoordinateCommand();
	~ShRelativeCoordinateCommand();

public:
	virtual void interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command);
	virtual bool isMatched(const QString &command);

private:
	void convertCoordinate(const QString &command, double &x, double &y);

};

//////////////////////////////////////////////////////

class ShPolarCoordinateCommand : public ShCommand {

public:
	ShPolarCoordinateCommand();
	~ShPolarCoordinateCommand();

public:
	virtual void interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command);
	virtual bool isMatched(const QString &command);

private:
	void convertCoordinate(const QString &command, double &angle, double &length);

};

///////////////////////////////////////////////////////

class ShDistanceFromBaseCommand : public ShCommand {

public:
	ShDistanceFromBaseCommand();
	~ShDistanceFromBaseCommand();

public:
	virtual void interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command);
	virtual bool isMatched(const QString &command);

};

#endif //_SHCOMMAND_H