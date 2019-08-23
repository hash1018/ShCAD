
#include "ShActionTypeConverter.h"

ShActionTypeConverter::ShActionTypeConverter() {

}

ShActionTypeConverter::~ShActionTypeConverter() {


}

QString ShActionTypeConverter::convert(ActionType actionType) {

	QString text;

	switch (actionType)
	{
	case ActionType::ActionDefault:
		text = ""; break;
	case ActionType::ActionDrawLine:
		text = "_Line"; break;
	case ActionType::ActionModifyMove:
		text = "_Move"; break;
	case ActionType::ActionModifyCopy:
		text = "_Copy"; break;
	case ActionType::ActionModifyRotate:
		text = "_Rotate"; break;
	case ActionType::ActionModifyMirror:
		text = "_Mirror"; break;

	default:
		text = ""; break;
	}

	return text;

}

ActionType ShActionTypeConverter::convert(const QString &text) {

	return ActionType::ActionUnknown;

}