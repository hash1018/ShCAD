
#ifndef _SHCADREQUESTSTRATEGY_H
#define _SHCADREQUESTSTRATEGY_H

class ShCAD;
class ShRequest;
class ShCADRequestStrategy {

protected:
	ShCAD *shCAD;
	ShRequest *request;

public:
	ShCADRequestStrategy(ShCAD *shCAD, ShRequest *request);
	virtual ~ShCADRequestStrategy() = 0;

	virtual void response() = 0;
};

class ShCADRequestCreateNewWidgetStrategy : public ShCADRequestStrategy {

public:
	ShCADRequestCreateNewWidgetStrategy(ShCAD *shCAD, ShRequest *request);
	~ShCADRequestCreateNewWidgetStrategy();

	virtual void response();

};

class ShCADRequestChangeActionStrategy : public ShCADRequestStrategy {

public:
	ShCADRequestChangeActionStrategy(ShCAD *shCAD, ShRequest *request);
	~ShCADRequestChangeActionStrategy();

	virtual void response();
};

class ShCADRequestSendNotifyEventStrategy : public ShCADRequestStrategy {

public:
	ShCADRequestSendNotifyEventStrategy(ShCAD *shCAD, ShRequest *request);
	~ShCADRequestSendNotifyEventStrategy();

	virtual void response();
};

class ShCADRequestUndoStrategy : public ShCADRequestStrategy {

public:
	ShCADRequestUndoStrategy(ShCAD *shCAD, ShRequest *request);
	~ShCADRequestUndoStrategy();

	virtual void response();
};

class ShCADRequestRedoStrategy : public ShCADRequestStrategy {

public:
	ShCADRequestRedoStrategy(ShCAD *shCAD, ShRequest *request);
	~ShCADRequestRedoStrategy();

	virtual void response();
};


#endif //_SHCADREQUESTSTRATEGY_H