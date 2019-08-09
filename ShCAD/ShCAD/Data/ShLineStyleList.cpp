
#include "ShLineStyleList.h"

ShLineStyleList ShLineStyleList::instance;

ShLineStyleList::ShLineStyleList() {

	this->list.append(ShLineStyle(0xFFFF));
	this->list.append(ShLineStyle(0x0101));
	this->list.append(ShLineStyle(0x00FF));
	this->list.append(ShLineStyle(0x10FF));
}

ShLineStyleList::~ShLineStyleList() {

}

ShLineStyleList* ShLineStyleList::getInstance() {

	return &(ShLineStyleList::instance);
}

int ShLineStyleList::search(const ShLineStyle& lineStyle) {

	return this->list.indexOf(lineStyle);
}

int ShLineStyleList::search(unsigned short pattern) {

	for (int i = 0; i < this->list.size(); i++) {

		if (this->list.at(i).getPattern() == pattern)
			return i;
	}

	return -1;
}