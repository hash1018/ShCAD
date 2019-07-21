
#include "ShKeyFlyWeight.h"
#include "ShKey.h"

ShKeyFlyWeight::ShKeyFlyWeight() {

}

ShKeyFlyWeight::~ShKeyFlyWeight() {

	for (int i = 0; i < this->pool.size(); i++)
		delete this->pool.at(i);
}

void ShKeyFlyWeight::add(ShKey *key) {

	this->pool.append(key);
}

ShKey* ShKeyFlyWeight::search(KeyType keyType) {

	for (int i = 0; i < this->pool.size(); i++) {
	
		if (this->pool.at(i)->getKeyType() == keyType)
			return this->pool.at(i);
	}

	return nullptr;
}

///////////////////////////////////////////

ShKeyFactory ShKeyFactory::instance;

ShKeyFactory::ShKeyFactory() {

}

ShKeyFactory::~ShKeyFactory() {

}

ShKeyFactory* ShKeyFactory::getInstance() {

	return &(ShKeyFactory::instance);
}

ShKey* ShKeyFactory::get(KeyType keyType) {

	ShKey *key = this->flyWeight.search(keyType);

	if (key == nullptr) {
	
		key = this->create(keyType);
		this->flyWeight.add(key);
	}

	return key;
}

ShKey* ShKeyFactory::create(KeyType keyType) {

	if (keyType == KeyType::Enter)
		return new ShEnterKey;
	else if (keyType == KeyType::Return)
		return new ShReturnKey;
	else if (keyType == KeyType::EscBackToPrevious)
		return new ShEscKey(KeyType::EscBackToPrevious);
	else if (keyType == KeyType::EscCancelCurrent)
		return new ShEscKey(KeyType::EscCancelCurrent);

	return new ShEnterKey;
}