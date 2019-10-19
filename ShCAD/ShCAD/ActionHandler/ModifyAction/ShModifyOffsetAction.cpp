
#include "ShModifyOffsetAction.h"

ShModifyOffsetAction::ShModifyOffsetAction(ShCADWidget *widget)
	:ShModifyAction(widget) {

}

ShModifyOffsetAction::~ShModifyOffsetAction() {

}

void ShModifyOffsetAction::mouseLeftPressEvent(ShActionData &data) {

}

void ShModifyOffsetAction::mouseMoveEvent(ShActionData &data) {

}

ActionType ShModifyOffsetAction::getType() {

	return ActionType::ActionModifyOffset;
}

QString ShModifyOffsetAction::getHeadTitle() {

	return QString();
}

void ShModifyOffsetAction::finishSelectingEntities() {


}

void ShModifyOffsetAction::invalidate(ShPoint3d &point) {

}

void ShModifyOffsetAction::trigger(const ShPoint3d &point) {


}