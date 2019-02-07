

#ifndef _SHCREATORVIEWUPDATEFACTORY_H
#define _SHCREATORVIEWUPDATEFACTORY_H

class ShViewUpdateStrategy;
class ShGraphicView;
class ShNotifyEvent;
class ShCreatorViewUpdateFactory {

public:
	ShCreatorViewUpdateFactory();
	~ShCreatorViewUpdateFactory();

	static ShViewUpdateStrategy* Create(ShGraphicView *view, ShNotifyEvent *event);
};

#endif //_SHCREATORVIEWUPDATEFACTORY_H