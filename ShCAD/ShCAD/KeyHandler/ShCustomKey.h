
#ifndef _SHCUSTOMKEY_H
#define _SHCUTEOMKEY_H

#include "KeyHandler\ShKey.h"

template <class T>
class ShCustomKey : public ShKey{

private:
	T *receiver;
	void (T::*method)();

public:
	ShCustomKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier, T *receiver, void (T::*method)());
	~ShCustomKey();

	virtual void press();

};

template <class T>
ShCustomKey<T>::ShCustomKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier, T *receiver, void (T::*method)())
	:ShKey(key, modifier), receiver(receiver), method(method) {

}

template <class T>
ShCustomKey<T>::ShCustomKey::~ShCustomKey() {


}

template <class T>
void ShCustomKey<T>::ShCustomKey::press() {

	(this->receiver->*method)();
}


#endif //_SHCUSTOMKEY_H