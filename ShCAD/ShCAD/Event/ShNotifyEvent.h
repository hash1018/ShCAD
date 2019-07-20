
#ifndef _SHNOTIFYEVENT_H
#define _SHNOTIFYEVENT_H

#include "Data\ShPoint.h"
#include <qstring.h>
class QKeyEvent;
class ShCADWidget;



#define shReplaceCommandHeadTitle(widget,headTitle) ShUpdateCommandHeadTitleEvent notifyEvent(headTitle); widget->notify(&notifyEvent)
#define shAddEditTextAndNewHeadTitleWithText(widget,text) ShUpdateTextToCommandListEvent notifyEvent(text, ShUpdateTextToCommandListEvent::EditTextAndNewLineHeadTitleWithText);widget->notify(&notifyEvent)


class ShNotifyEvent {

public:
	enum Type {
		Nothing,
		ZoomRateChanged,
		MousePositionChanged,
		KeyPressed,
		ActivatedWidgetChanged,
		UpdateTextToCommandList,
		UpdateCommandHeadTitle,
	};

	ShNotifyEvent(Type type);
	virtual ~ShNotifyEvent() = 0;

	inline Type getType() const { return this->type; }

protected:
	Type type;

};

/////////////////////////////////////////////////////////////////////

class ShZoomRateChangedEvent : public ShNotifyEvent {

public:
	ShZoomRateChangedEvent(const double &zoomRate);
	~ShZoomRateChangedEvent();

	inline double getZoomRate() const { return this->zoomRate; }

private:
	double zoomRate;
};

//////////////////////////////////////////////////////////////////////

class ShMousePositionChangedEvent : public ShNotifyEvent {

public:
	ShMousePositionChangedEvent(const ShPoint3d &point);
	~ShMousePositionChangedEvent();

	inline ShPoint3d getPoint() const { return this->point; }
private:
	ShPoint3d point;
};

///////////////////////////////////////////////////////////////////////


class ShKeyPressedEvent : public ShNotifyEvent {

public:
	ShKeyPressedEvent(QKeyEvent *event);
	~ShKeyPressedEvent();

	inline QKeyEvent* getEvent() const { return this->event; }

protected:
	QKeyEvent *event;
};


//////////////////////////////////////////////////////////////////////

class ShActivatedWidgetChangedEvent : public ShNotifyEvent {

public:
	ShActivatedWidgetChangedEvent(ShCADWidget *newWidget, ShCADWidget *previousWidget);
	~ShActivatedWidgetChangedEvent();

	inline ShCADWidget* getNewWidget() const { return this->newWidget; }
	inline ShCADWidget* getPreviousWidget() const { return this->previousWidget; }

private:
	ShCADWidget *newWidget;
	ShCADWidget *previousWidget;
};

//////////////////////////////////////////////////////////////////////

class ShUpdateTextToCommandListEvent : public ShNotifyEvent {

public:
	enum UpdateType {
		EditTextWithText,
		EditTextAndNewLineHeadTitleWithText,
		OnlyText,
	};

public:
	ShUpdateTextToCommandListEvent(const QString &text, ShUpdateTextToCommandListEvent::UpdateType type = UpdateType::EditTextWithText);
	~ShUpdateTextToCommandListEvent();

	inline QString getText() const { return this->text; }
	inline UpdateType getUpdateType() const { return this->updateType; }

private:
	QString text;
	UpdateType updateType;

};

/////////////////////////////////////////////////////////////////////////

class ShUpdateCommandHeadTitleEvent : public ShNotifyEvent {

public:
	enum UpdateType {
		AddHeadTitleToCurrent,
		ReplaceHeadTitle,
	};

public:
	ShUpdateCommandHeadTitleEvent(const QString &headTitle, UpdateType type = ReplaceHeadTitle);
	~ShUpdateCommandHeadTitleEvent();

	inline QString getHeadTitle() const { return this->headTitle; }
	inline UpdateType getUpdateType() const { return this->updateType; }

private:
	QString headTitle;
	UpdateType updateType;
};

#endif //_SHNOTIFYEVENT_H