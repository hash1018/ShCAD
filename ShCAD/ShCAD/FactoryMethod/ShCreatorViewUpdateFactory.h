

#ifndef _SHCREATORVIEWUPDATEFACTORY_H
#define _SHCREATORVIEWUPDATEFACTORY_H

class ShViewUpdateHandler;
class ShGraphicView;
class ShNotifyEvent;
class ShCreatorViewUpdateFactory {

public:
	ShCreatorViewUpdateFactory();
	~ShCreatorViewUpdateFactory();

	static ShViewUpdateHandler* Create(ShGraphicView *view, ShNotifyEvent *event);
};

#endif //_SHCREATORVIEWUPDATEFACTORY_H