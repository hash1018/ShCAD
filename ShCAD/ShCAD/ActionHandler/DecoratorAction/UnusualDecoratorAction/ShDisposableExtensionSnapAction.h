

#ifndef _SHDISPOSABLEEXTENSIONSNAPACTION_H
#define _SHDISPOSABLEEXTENSIONSNAPACTION_H

#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"
#include <qlist.h>
#include <qobject.h>

class ShExtensionBaseData {

	friend class ShDisposableExtensionSnapAction;

private:
	QList<ShEntity*> baseEntities;
	ShPoint3d point;

public:
	ShExtensionBaseData();
	~ShExtensionBaseData();

	ShExtensionBaseData& operator=(const ShExtensionBaseData &other);
};

class ShLastDeletePoint {

	friend class ShDisposableExtensionSnapAction;

private:
	bool deleted;
	ShPoint3d lastDeletePoint;

private:
	ShLastDeletePoint();
	~ShLastDeletePoint();

};

class ShLastAddedPoint {

	friend class ShDisposableExtensionSnapAction;

private:
	bool added;
	ShPoint3d lastAddedPoint;

private:
	ShLastAddedPoint();
	~ShLastAddedPoint();
};

class ShDisposableExtensionSnapAction : public ShDisposableSnapAction, public QObject {
	
private:
	QList<ShExtensionBaseData> extensionBaseDatas;
	ShLastDeletePoint lastDeletePoint;
	ShLastAddedPoint lastAddedPoint;

public:
	ShDisposableExtensionSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableExtensionSnapAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	void updateExtensionBaseData(const ShPoint3d &point);

	private slots:
	void initializeLastDeletePoint();
	void initializeLastAddedPoint();
};

#endif //_SHDISPOSABLEEXTENSIONSNAPACTION_H