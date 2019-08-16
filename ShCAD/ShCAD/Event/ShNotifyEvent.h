
#ifndef _SHNOTIFYEVENT_H
#define _SHNOTIFYEVENT_H

#include "Data\ShPoint.h"
#include <qstring.h>

class QKeyEvent;
class ShCADWidget;
class ShColor;
class ShLineStyle;
class ShLayer;



#define shReplaceCommandHeadTitle(widget,headTitle) ShUpdateCommandHeadTitleEvent evt(headTitle); widget->notify(&evt)
#define shAddEditTextAndNewHeadTitleWithText(widget,text) ShUpdateTextToCommandListEvent evt(text, ShUpdateTextToCommandListEvent::EditTextAndNewLineHeadTitleWithText);widget->notify(&evt)


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
		CurrentColorChanged,
		CurrentLineStyleChanged,
		TransactionStackSizeChanged,
		CurrentLayerChanged,
		LayerDataChanged,
		LayerCreated,
		LayerDeleted,
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

///////////////////////////////////////////////////////////////////////////

class ShCurrentColorChangedEvent : public ShNotifyEvent {

public:
	ShCurrentColorChangedEvent(const ShColor &color);
	~ShCurrentColorChangedEvent();

	inline const ShColor& getColor() const { return this->color; }

private:
	const ShColor &color;
};

////////////////////////////////////////////////////////////////////////////

class ShCurrentLineStyleChangedEvent : public ShNotifyEvent {

public:
	ShCurrentLineStyleChangedEvent(const ShLineStyle &lineStyle);
	~ShCurrentLineStyleChangedEvent();

	inline const ShLineStyle& getLineStyle() const { return this->lineStyle; }

private:
	const ShLineStyle &lineStyle;
};

/////////////////////////////////////////////////////////////////////////////

class ShTransactionStackSizeChangedEvent : public ShNotifyEvent {

public:
	ShTransactionStackSizeChangedEvent(const int &undoSize, const int &redoSize);
	~ShTransactionStackSizeChangedEvent();

	inline int getUndoSize() const { return this->undoSize; }
	inline int getRedoSize() const { return this->redoSize; }

private:
	int undoSize;
	int redoSize;

};

//////////////////////////////////////////////////////////////////////////////

class ShCurrentLayerChangedEvent : public ShNotifyEvent {

public:
	ShCurrentLayerChangedEvent(ShLayer *currentLayer);
	~ShCurrentLayerChangedEvent();

	inline ShLayer* getCurrentLayer() const { return this->currentLayer; }

private:
	ShLayer *currentLayer;
};

///////////////////////////////////////////////////////////////////////////////

class ShLayerDataChangedEvent : public ShNotifyEvent {

public:
	enum ChangedType {
		Color,
		LineStyle,
		Name,
		Turn,
	};

public:
	ShLayerDataChangedEvent(ShLayer *layer, const ShColor &color, bool current = false);
	ShLayerDataChangedEvent(ShLayer *layer, const ShLineStyle &lineStyle, bool current = false);
	ShLayerDataChangedEvent(ShLayer *layer, const QString &name, bool current = false);
	ShLayerDataChangedEvent(ShLayer *layer, bool turn, bool current = false);
	~ShLayerDataChangedEvent();

public:
	inline ShLayer* getLayer() const { return this->layer; }
	inline bool isCurrent() const { return this->current; }
	inline const ShColor* getColor() const { return this->color; }
	inline const ShLineStyle* getLineStyle() const { return this->lineStyle; }
	inline const QString* getName() const { return this->name; }
	inline ChangedType getChangedType() const { return this->changedType;}
	inline bool getTurn() const { return this->turn; }


private:
	ChangedType changedType;
	ShLayer *layer;
	bool current;
	const ShColor *color;
	const ShLineStyle *lineStyle;
	const QString *name;
	bool turn;
	
};

///////////////////////////////////////////////////////////////////////////////

class ShLayerCreatedEvent : public ShNotifyEvent {

public:
	ShLayerCreatedEvent(ShLayer *createdLayer);
	~ShLayerCreatedEvent();

	inline ShLayer* getCreatedLayer() const { return this->createdLayer; }

private:
	ShLayer *createdLayer;

};

////////////////////////////////////////////////////////////////////////////////

class ShLayerDeletedEvent : public ShNotifyEvent {

public:
	ShLayerDeletedEvent(ShLayer *deletedLayer);
	~ShLayerDeletedEvent();

	inline ShLayer* getDeletedLayer() const { return this->deletedLayer; }

private:
	ShLayer *deletedLayer;

};

#endif //_SHNOTIFYEVENT_H