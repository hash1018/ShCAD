

#ifndef _SHOBJECTSNAPSTATE_H
#define _SHOBJECTSNAPSTATE_H

class QMouseEvent;
class ShObjectSnapState {

public:
	ShObjectSnapState();
	virtual ~ShObjectSnapState() = 0;

	virtual void MousePressEvent(QMouseEvent *event) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event) = 0;

};


class ShObjectSnapState_Nothing : public ShObjectSnapState {

public:
	ShObjectSnapState_Nothing();
	~ShObjectSnapState_Nothing();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);
};

class ShObjectSnapState_EndPoint : public ShObjectSnapState {

public:
	ShObjectSnapState_EndPoint();
	~ShObjectSnapState_EndPoint();

	virtual void MousePressEvent(QMouseEvent *event);
	virtual void MouseMoveEvent(QMouseEvent *event);

};


#endif //_SHOBJECTSNAPSTATE_H