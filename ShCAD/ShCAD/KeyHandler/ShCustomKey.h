
#ifndef _SHCUSTOMKEY_H
#define _SHCUTEOMKEY_H

#include "KeyHandler\ShKey.h"

class ShAbstractCustomKey : public ShKey {

public:
	ShAbstractCustomKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier)
		:ShKey(KeyType::Custom, key, modifier) {
	}

	virtual ~ShAbstractCustomKey() {
	
	}

};

template <class T>
class ShCustomKey : public ShAbstractCustomKey{

private:
	T *receiver;
	void (T::*method)();

public:
	ShCustomKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier, T *receiver, void (T::*method)());
	~ShCustomKey();

	virtual void pressed(ShCADWidget *widget, ShActionHandler *actionHandler);

};

template <class T>
ShCustomKey<T>::ShCustomKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier, T *receiver, void (T::*method)())
	:ShAbstractCustomKey(key, modifier), receiver(receiver), method(method) {

}

template <class T>
ShCustomKey<T>::ShCustomKey::~ShCustomKey() {


}

template <class T>
void ShCustomKey<T>::ShCustomKey::pressed(ShCADWidget *widget, ShActionHandler *actionHandler) {

	(this->receiver->*method)();
}


#endif //_SHCUSTOMKEY_H