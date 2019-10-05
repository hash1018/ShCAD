
#ifndef _SHOBSERVER_H
#define _SHOBSERVER_H

class ShNotifyEvent;

class ShObserver {

public:
	ShObserver() {}
	~ShObserver() {}

	virtual void update(ShNotifyEvent *event) = 0;

};

#endif //_SHOBSERVER_H
