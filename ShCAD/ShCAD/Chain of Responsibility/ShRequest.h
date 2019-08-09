
#ifndef _SHREQUEST_H
#define _SHREQUEST_H

class ShChangeActionStrategy;
class ShNotifyEvent;

class ShRequest {

public:
	enum RequestType {
		RequestCreateNewCADWidget,
		RequestChangeActionHandler,
		RequestSendNotifyEvent,

	};

protected:
	RequestType type;

public:
	ShRequest(RequestType type);
	virtual ~ShRequest() = 0;

	inline RequestType getType() const { return this->type; }

};

class ShCreateNewCADWidgetRequest : public ShRequest {

public:
	ShCreateNewCADWidgetRequest();
	~ShCreateNewCADWidgetRequest();

};

class ShRequestChangeActionHandler : public ShRequest {

private:
	ShChangeActionStrategy *strategy;

public:
	ShRequestChangeActionHandler(ShChangeActionStrategy *strategy);
	~ShRequestChangeActionHandler();

	inline ShChangeActionStrategy* getStrategy() const { return this->strategy; }
};

class ShRequestSendNotifyEvent : public ShRequest {

private:
	ShNotifyEvent *notifyEvent;

public:
	ShRequestSendNotifyEvent(ShNotifyEvent *notifyEvent);
	~ShRequestSendNotifyEvent();

	inline ShNotifyEvent* getNotifyEvent() const { return this->notifyEvent; }
};

#endif //_SHREQUEST_H