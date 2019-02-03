

#ifndef _SHNOTIFYEVENTUPDATEHANDLER_H
#define _SHNOTIFYEVENTUPDATEHANDLER_H


//transformed Strategy Pattern.

class ShGraphicView;
class ShNotifyEvent;
class ShViewUpdateHandler;
class ShNotifyEventUpdateHandler {

private:
	ShViewUpdateHandler *updateHandler;

public:
	ShNotifyEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShNotifyEventUpdateHandler();

	void Update();


};

class ShViewUpdateHandler {

protected:
	ShNotifyEvent *event;
	ShGraphicView *view;

public:
	ShViewUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	virtual ~ShViewUpdateHandler() = 0;

	virtual void Update() = 0;

};

class ShKeyPressedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShKeyPressedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShKeyPressedEventUpdateHandler();

	virtual void Update();
};

class ShPropertyColorComboSelChangedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShPropertyColorComboSelChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyColorComboSelChangedEventUpdateHandler();

	virtual void Update();

};

class ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0 : public ShViewUpdateHandler {

public:
	ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyColorComboSelChangedEventUpdateHandlerSelectedEntity0();

	virtual void Update();
};

class ShPropertyLineStyleComboSelChangedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShPropertyLineStyleComboSelChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyLineStyleComboSelChangedEventUpdateHandler();

	virtual void Update();
};

class ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0 : public ShViewUpdateHandler {

public:
	ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyLineStyleComboSelChangedEventUpdateHandlerSelectedEntity0();

	virtual void Update();

};

class ShLayerComboSelChangedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShLayerComboSelChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerComboSelChangedEventUpdateHandler();

	virtual void Update();

};

class ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0 : public ShViewUpdateHandler {

public:
	ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerComboSelChangedEventUpdateHandlerSelectedEntity0();

	virtual void Update();

};

class ShLayerDataChangedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShLayerDataChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerDataChangedEventUpdateHandler();

	virtual void Update();

};

class ShLayerDataChangedEventUpdateHandlerSelectedEntity0 : public ShViewUpdateHandler {

public:
	ShLayerDataChangedEventUpdateHandlerSelectedEntity0(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerDataChangedEventUpdateHandlerSelectedEntity0();

	virtual void Update();

};

class ShLayerCreatedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShLayerCreatedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerCreatedEventUpdateHandler();

	virtual void Update();

};

class ShLayerDeletedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShLayerDeletedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerDeletedEventUpdateHandler();

	virtual void Update();

};

class ShCurrentLayerChangedEventUpdateHandler : public ShViewUpdateHandler {

public:
	ShCurrentLayerChangedEventUpdateHandler(ShGraphicView *view, ShNotifyEvent *event);
	~ShCurrentLayerChangedEventUpdateHandler();

	virtual void Update();

};


















/*
class ShKeyPressedEvent;
class ShPropertyColorComboSelChangedEvent;
class ShPropertyLineStyleComboSelChangedEvent;
class ShLayerComboSelChangedEvent;
class ShLayerCreatedEvent;
class ShLayerDataChangedEvent;
class ShLayerDeletedEvent;

class ShViewUpdateHandler : public ShNotifyEventUpdateHandler {
	friend class ShNotifyEventUpdateHandler;

private:
	ShGraphicView *view;

private:
	ShViewUpdateHandler(ShGraphicView *view);
	~ShViewUpdateHandler();

	
	virtual void Update(ShNotifyEvent *event);
	void Update(ShKeyPressedEvent *event);
    void Update(ShPropertyColorComboSelChangedEvent *event);
	void Update(ShPropertyLineStyleComboSelChangedEvent *event);
	void Update(ShLayerComboSelChangedEvent *event);
	void Update(ShLayerDataChangedEvent *event);
	void Update(ShLayerCreatedEvent *event);
	void Update(ShLayerDeletedEvent *event);


};

class ShViewUpdateHandlerSelectedEntityCount0 : public ShNotifyEventUpdateHandler {
	friend class ShNotifyEventUpdateHandler;

private:
	ShGraphicView *view;

private:
	ShViewUpdateHandlerSelectedEntityCount0(ShGraphicView *view);
	~ShViewUpdateHandlerSelectedEntityCount0();


	virtual void Update(ShNotifyEvent *event);
	void Update(ShKeyPressedEvent *event);
	void Update(ShPropertyColorComboSelChangedEvent *event);
	void Update(ShPropertyLineStyleComboSelChangedEvent *event);
	void Update(ShLayerComboSelChangedEvent *event);
	void Update(ShLayerDataChangedEvent *event);
	void Update(ShLayerCreatedEvent *event);
	void Update(ShLayerDeletedEvent *event);
};



class ShViewKeyPressEventUpdateHandler : public ShNotifyEventUpdateHandler {

private:
	ShNotifyEvent

};

*/
#endif //_SHNOTIFYEVENTUPDATEHANDLER_H