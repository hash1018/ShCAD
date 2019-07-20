
#ifndef _SHCUSTOMKEY_H
#define _SHCUTEOMKEY_H

#include "KeyHandler\ShKey.h"

template <class T>
class ShCustomKey : public ShKey{

private:
	T *sender;
	void (T::*method)();

public:
	ShCustomKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier, T *sender, void (T::*method)());
	~ShCustomKey();

	virtual void press();

};

template <class T>
ShCustomKey<T>::ShCustomKey(const Qt::Key &key, const Qt::KeyboardModifiers &modifier, T *sender, void (T::*method)())
	:ShKey(key, modifier), sender(sender), method(method) {

}

template <class T>
ShCustomKey<T>::ShCustomKey::~ShCustomKey() {


}

template <class T>
void ShCustomKey<T>::ShCustomKey::press() {

	(this->sender->*method)();
}


#endif //_SHCUSTOMKEY_H