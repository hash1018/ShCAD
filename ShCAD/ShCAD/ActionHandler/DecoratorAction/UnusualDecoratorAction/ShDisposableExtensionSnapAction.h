

#ifndef _SHDISPOSABLEEXTENSIONSNAPACTION_H
#define _SHDISPOSABLEEXTENSIONSNAPACTION_H

#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"
#include <qlist.h>

class ShExtensionBaseData {

	friend class ShDisposableExtensionSnapAction;

private:
	QList<ShEntity*> baseEntities;
	ShPoint3d point;

private:
	ShExtensionBaseData();
	~ShExtensionBaseData();

	ShExtensionBaseData& operator=(const ShExtensionBaseData &other);
};

class ShDisposableExtensionSnapAction : public ShDisposableSnapAction {

private:
	QList<ShExtensionBaseData> ShExtensionBaseDatas;

public:
	ShDisposableExtensionSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableExtensionSnapAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	virtual bool search(const ShPoint3d &point);

};

#endif //_SHDISPOSABLEEXTENSIONSNAPACTION_H