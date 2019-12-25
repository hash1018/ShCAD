
#include "ShDimAligned.h"
#include "Entity\Private\Algorithm\ShVisitor.h"
#include "Base\ShMath.h"
#include "Base\ShDimensionStyle.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Leaf\ShLine.h"

ShDimAligned::ShDimAligned(const ShDimAlignedData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle)
	:ShDim(propertyData, layer, dimensionStyle), data(data) {

	this->updateChild();
}

ShDimAligned::ShDimAligned(const ShDimAligned &other)
	: ShDim(other), data(other.data) {

	this->updateChild();
}

ShDimAligned::~ShDimAligned() {

}

ShDimAligned& ShDimAligned::operator=(const ShDimAligned &other) {

	ShDim::operator=(other);

	this->data = other.data;
	this->updateChild();

	return *this;
}

ShDimAligned* ShDimAligned::clone() {

	return new ShDimAligned(*this);
}

void ShDimAligned::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShDimAligned::updateChild() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();

	this->list.append(new ShDot(this->data.firstOrigin, this->propertyData, this->layer));
	this->list.append(new ShDot(this->data.secondOrigin, this->propertyData, this->layer));

	ShLine *extensionLine = const_cast<ShDimensionExtensionLineStyle&>(this->dimensionStyle->getDimensionExtensionLineStyle()).
		createExtensionLine(this->data.firstOrigin, this->data.firstDim, this->propertyData, this->layer);

	if (extensionLine != nullptr)
		this->list.append(extensionLine);

	extensionLine = const_cast<ShDimensionExtensionLineStyle&>(this->dimensionStyle->getDimensionExtensionLineStyle()).
		createExtensionLine2(this->data.secondOrigin, this->data.secondDim, this->propertyData, this->layer);

	if (extensionLine != nullptr)
		this->list.append(extensionLine);

	this->list.append(new ShLine(this->propertyData, ShLineData(this->data.firstDim, this->data.secondDim), this->layer));
	this->list.append(new ShLine(this->propertyData, ShLineData(this->data.firstDim, this->data.text), this->layer));
}

void ShDimAligned::setData(const ShDimAlignedData &data) {

	this->data = data;
	this->updateChild();
}

double ShDimAligned::getDistance() {

	return math::getDistance(this->data.firstDim.x, this->data.firstDim.y, this->data.secondDim.x, this->data.secondDim.y);
}

void ShDimAligned::getFirstArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	this->dimensionStyle->getDimensionArrowStyle().
		getFirstLineArrowPoints(this->data.firstDim, this->data.secondDim, vertex, vertex2, vertex3);
}

void ShDimAligned::getSecondArrowPoints(ShPoint3d &vertex, ShPoint3d &vertex2, ShPoint3d &vertex3) {

	this->dimensionStyle->getDimensionArrowStyle().
		getSecondLineArrowPoints(this->data.firstDim, this->data.secondDim, vertex, vertex2, vertex3);
}