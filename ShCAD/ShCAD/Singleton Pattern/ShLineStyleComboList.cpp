

#include "ShLineStyleComboList.h"

ShLineStyleComboList ShLineStyleComboList::instance;

ShLineStyleComboList::ShLineStyleComboList() {

	this->layerStyle.type = ShLineStyle::Type::ByLayer;
	this->blockStyle.type = ShLineStyle::Type::ByBlock;

	this->list.append(ShLineStyle(0xFFFF));  //continuous
	this->list.append(ShLineStyle(0x0101));  //dotted
	this->list.append(ShLineStyle(0x00FF));  //dashed
	this->list.append(ShLineStyle(0x1C47));  //dash/dot/dash


}

ShLineStyleComboList::~ShLineStyleComboList() {

}

ShLineStyleComboList* ShLineStyleComboList::GetInstance() {

	return &(ShLineStyleComboList::instance);
}


QString ShLineStyleComboList::GetLayerLineStyleText() {

	return "ByLayer " + this->GetLineStyleShape(this->layerStyle.pattern);
}

QString ShLineStyleComboList::GetBlockLineStyleText() {

	return "ByBlock " + this->GetLineStyleShape(this->blockStyle.pattern);
}

QString ShLineStyleComboList::GetLineStyleText(int index) {

	ShLineStyle lineStyle = this->list.at(index);
	unsigned short pattern = lineStyle.pattern;
	QString shape = this->GetLineStyleShape(pattern);

	if (pattern == 0xFFFF)
		return "Solid " + shape;
	else if (pattern == 0x0101)
		return "Dotted " + shape;
	else if (pattern == 0x00FF)
		return "Dashed" + shape;

	return "Dash-Dot-Dash " + shape;
}

QString ShLineStyleComboList::GetLineStyleShape(unsigned short pattern) {

	if (pattern == 0xFFFF) {
		return QString::fromLocal8Bit("式式式式式式式式");
	}

	else if (pattern == 0x0101) {
		return QString::fromLocal8Bit("﹞﹞﹞﹞﹞﹞﹞﹞﹞﹞﹞﹞﹞﹞﹞﹞");
	}
	else if (pattern == 0x00FF) {
		return QString::fromLocal8Bit("-----------------");
	}
	
	return QString::fromLocal8Bit("-﹞-﹞-﹞-﹞-﹞-");
}

ShLineStyle ShLineStyleComboList::GetColorUsingComboBoxIndex(int comboBoxIndex) {

	if (comboBoxIndex == 0)
		return this->blockStyle;
	else if (comboBoxIndex == 1)
		return this->layerStyle;


	return this->list.at(comboBoxIndex - 2);
}