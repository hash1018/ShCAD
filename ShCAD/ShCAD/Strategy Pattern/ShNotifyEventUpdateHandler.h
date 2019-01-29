

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
class ShLayerDataChangedEvent;

class ShGraphicViewUpdateHandler : public ShNotifyEventUpdateHandler {
	friend class ShNotifyEventUpdateHandler;

private:
	ShGraphicView *view;

private:
	ShGraphicViewUpdateHandler(ShGraphicView *view);
	~ShGraphicViewUpdateHandler();

	
	virtual void Update(ShNotifyEvent *event);
	virtual void Update(ShKeyPressedEvent *event);
	virtual void Update(ShPropertyColorComboSelChangedEvent *event);
	virtual void Update(ShPropertyLineStyleComboSelChangedEvent *event);
	virtual void Update(ShCurrentLayerChangedEvent *event);
	virtual void Update(ShLayerDataChangedEvent *event);


};


#endif //_SHNOTIFYEVENTUPDATEHANDLER_H