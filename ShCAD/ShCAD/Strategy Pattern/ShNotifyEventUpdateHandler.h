

#ifndef _SHNOTIFYEVENTUPDATEHANDLER_H
#define _SHNOTIFYEVENTUPDATEHANDLER_H


//transformed Strategy Pattern.

class ShGraphicView;
class ShNotifyEvent;
class ShNotifyEventUpdateHandler {

private:
	ShNotifyEventUpdateHandler *updateHandler;

public:
	ShNotifyEventUpdateHandler(ShGraphicView *view);
	~ShNotifyEventUpdateHandler();

	virtual void Update(ShNotifyEvent *event);

protected:
	ShNotifyEventUpdateHandler();

};

class ShKeyPressedEvent;
class ShPropertyColorComboSelChangedEvent;
class ShPropertyLineStyleComboSelChangedEvent;
class ShCurrentLayerChangedEvent;
class ShLayerCreatedEvent;
class ShLayerDataChangedEvent;
class ShLayerDeletedEvent;

class ShGraphicViewUpdateHandler : public ShNotifyEventUpdateHandler {
	friend class ShNotifyEventUpdateHandler;

private:
	ShGraphicView *view;

private:
	ShGraphicViewUpdateHandler(ShGraphicView *view);
	~ShGraphicViewUpdateHandler();

	
	virtual void Update(ShNotifyEvent *event);
	void Update(ShKeyPressedEvent *event);
    void Update(ShPropertyColorComboSelChangedEvent *event);
	void Update(ShPropertyLineStyleComboSelChangedEvent *event);
	void Update(ShCurrentLayerChangedEvent *event);
	void Update(ShLayerDataChangedEvent *event);
	void Update(ShLayerCreatedEvent *event);
	void Update(ShLayerDeletedEvent *event);


};


#endif //_SHNOTIFYEVENTUPDATEHANDLER_H