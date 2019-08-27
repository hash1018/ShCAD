

#ifndef _SHCUSTOMCOMMAND_H
#define _SHCUSTOMCOMMAND_H

#include "ShCommand.h"

class ShAbstractCustomCommand : public ShCommand {

public:
	ShAbstractCustomCommand()
		:ShCommand(CommandType::CustomCommand) {
	
	}

	virtual ~ShAbstractCustomCommand() {
	
	}
	
};

template <class T>
class ShCustomCommand : public ShAbstractCustomCommand {

protected:
	T *receiver;
	void (T::*method)(void*);

public:
	ShCustomCommand(T *receiver, void (T::*method)(void*));
	virtual ~ShCustomCommand() = 0;
};

template <class T>
class ShOnlyNumberCommand : public ShCustomCommand <T> {

public:
	ShOnlyNumberCommand(T *receiver, void (T::*method)(void*));
	~ShOnlyNumberCommand();

public:
	virtual void interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command);
	virtual bool isMatched(const QString &command);
};

template <class T>
ShCustomCommand<T>::ShCustomCommand(T *receiver, void (T::*method)(void*))
	:receiver(receiver), method(method) {
	
}

template <class T>
ShCustomCommand<T>::~ShCustomCommand() {

}

/////////////////////////////////////////////////////

template <class T>
ShOnlyNumberCommand<T>::ShOnlyNumberCommand(T *receiver, void (T::*method)(void*))
	:ShCustomCommand<T>(receiver, method) {

	
}
	
template <class T>
ShOnlyNumberCommand<T>::~ShOnlyNumberCommand() {

}

template <class T>
void ShOnlyNumberCommand<T>::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	double number = command.toDouble();

	(this->receiver->*method)(&number);
}

template <class T>
bool ShOnlyNumberCommand<T>::isMatched(const QString &command) {
	
	return this->isNumber(command);
}


#endif //_SHCUSTOMCOMMAND_H