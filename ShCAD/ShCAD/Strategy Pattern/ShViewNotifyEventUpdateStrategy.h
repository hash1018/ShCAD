

#ifndef _SHVIEWNOTIFYEVENTUPDATESTRATEGY_H
#define _SHVIEWNOTIFYEVENTUPDATESTRATEGY_H



class ShGraphicView;
class ShNotifyEvent;
class ShViewUpdateStrategy;
class ShViewNotifyEventUpdateStrategy {

private:
	ShViewUpdateStrategy *strategy;

public:
	ShViewNotifyEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShViewNotifyEventUpdateStrategy();

	void Update();


};

class ShViewUpdateStrategy {

protected:
	ShNotifyEvent *event;
	ShGraphicView *view;

public:
	ShViewUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	virtual ~ShViewUpdateStrategy() = 0;

	virtual void Update() = 0;

};

class ShKeyPressedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShKeyPressedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShKeyPressedEventUpdateStrategy();

	virtual void Update();
};



class ShPropertyColorComboSelChangedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShPropertyColorComboSelChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyColorComboSelChangedEventUpdateStrategy();

	virtual void Update();

};

class ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0 : public ShViewUpdateStrategy {

public:
	ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyColorComboSelChangedEventUpdateStrategySelectedEntity0();

	virtual void Update();
};


class ShPropertyLineStyleComboSelChangedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShPropertyLineStyleComboSelChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyLineStyleComboSelChangedEventUpdateStrategy();

	virtual void Update();
};

class ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0 : public ShViewUpdateStrategy {

public:
	ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0(ShGraphicView *view, ShNotifyEvent *event);
	~ShPropertyLineStyleComboSelChangedEventUpdateStrategySelectedEntity0();

	virtual void Update();

};


class ShLayerComboSelChangedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShLayerComboSelChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerComboSelChangedEventUpdateStrategy();

	virtual void Update();

};

class ShLayerComboSelChangedEventUpdateStrategySelectedEntity0 : public ShViewUpdateStrategy {

public:
	ShLayerComboSelChangedEventUpdateStrategySelectedEntity0(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerComboSelChangedEventUpdateStrategySelectedEntity0();

	virtual void Update();

};

class ShLayerDataChangedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShLayerDataChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerDataChangedEventUpdateStrategy();

	virtual void Update();

};



class ShLayerCreatedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShLayerCreatedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerCreatedEventUpdateStrategy();

	virtual void Update();

};

class ShLayerDeletedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShLayerDeletedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShLayerDeletedEventUpdateStrategy();

	virtual void Update();

};

class ShCurrentLayerChangedEventUpdateStrategy : public ShViewUpdateStrategy {

public:
	ShCurrentLayerChangedEventUpdateStrategy(ShGraphicView *view, ShNotifyEvent *event);
	~ShCurrentLayerChangedEventUpdateStrategy();

	virtual void Update();

};



#endif //_SHVIEWNOTIFYEVENTUPDATESTRATEGY_H