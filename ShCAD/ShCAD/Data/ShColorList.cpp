
#include "ShColorList.h"


ShColorList ShColorList::instance;

ShColorList::ShColorList() {

	this->list.append(ShColor(255, 0, 0)); //red
	this->list.append(ShColor(255, 255, 0)); //yellow
	this->list.append(ShColor(0, 255, 0));  //green
	this->list.append(ShColor(0, 255, 255)); //sky
	this->list.append(ShColor(0, 0, 255));  //blue
	this->list.append(ShColor(255, 255, 255)); //white
}

ShColorList::~ShColorList() {

}

ShColorList* ShColorList::getInstance() {

	return &(ShColorList::instance);
}

int ShColorList::search(const ShColor &color) {

	return this->list.indexOf(color);
}

void ShColorList::add(const ShColor &color) {

	this->list.append(color);
}