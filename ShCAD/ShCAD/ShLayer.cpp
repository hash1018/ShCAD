

#include "ShLayer.h"

ShLayer::ShLayer() {

}

ShLayer::ShLayer(const ShLayerData& data)
	:data(data) {

}

ShLayer::ShLayer(const ShLayer& other)
	: data(other.data), list(other.list) {

	//shallow copy for list;

}

ShLayer::~ShLayer() {

}

void ShLayer::Add(ShEntity *entity) {

	this->list.append(entity);
}

void ShLayer::Remove(ShEntity *entity) {

	this->list.removeOne(entity);
}
