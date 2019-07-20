
#include "ShDrawAction.h"

ShDrawAction::ShDrawAction(ShCADWidget *widget)
	:ShActionHandler(widget) {

}

ShDrawAction::~ShDrawAction() {

}

QCursor ShDrawAction::getCursorShape() {

	return QCursor(Qt::CursorShape::CrossCursor);
}
