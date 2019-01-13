

#ifndef _SHVARIABLE_H
#define _SHVARIABLE_H


enum ActionType {
	ActionUnknown,
	ActionDefault,
	ActionDrawLine


};

enum MementoType {
	MementoUnknown,
	MementoCreated,
	MementoDeleted

};


enum DrawType {
	DrawNone = 0x0000000,
	DrawCaptureImage = 0x0000001,
	DrawPreviewEntities = 0x0000002,
	DrawAddedEntities = 0x0000004,
	DrawAll = 0x0001000

};

enum NotifyEvent {
	NotifyNothing=0x0000000,
	NotifyZoomRateChanged=0x00000001,
	NotifyMousePositionChanged=0x00000002

};
#endif //_SHVARIABLE_H