
#include "ShLineStyleConverter.h"

ShLineStyleConverter::ShLineStyleConverter() {

}

ShLineStyleConverter::~ShLineStyleConverter() {

}

QString ShLineStyleConverter::getLineStyleText(unsigned short pattern) {

	if (pattern == 0xFFFF)
		return "Solid ";
	else if (pattern == 0x0101)
		return "Dotted ";
	else if (pattern == 0x00FF)
		return "Dashed ";

	return "Dash-Dot-Dash ";
}

QString ShLineStyleConverter::getLineStyleShape(unsigned short pattern) {

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

