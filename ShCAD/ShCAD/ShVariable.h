

#ifndef _SHVARIABLE_H
#define _SHVARIABLE_H


enum ActionType {
	ActionUnknown,
	ActionDefault,
	ActionPanMove,
	ActionDragSelect,
	ActionDrawLine


};


enum DrawType {
	DrawNone = 0x0000000,
	DrawCaptureImage = 0x0000001,
	DrawPreviewEntities = 0x0000002,
	DrawAddedEntities = 0x0000004,
	DrawActionHandler = 0x00000008,
	DrawSelectedEntities=0x00000010,
	DrawAll = 0x0001000

};

enum NotifyEvent {
	NotifyNothing=0x0000000,
	NotifyZoomRateChanged=0x00000001,
	NotifyMousePositionChanged=0x00000002

};
#endif //_SHVARIABLE_H