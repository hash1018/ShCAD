

#ifndef _SHDISPOSABLEEXTENSIONSNAPACTION_H
#define _SHDISPOSABLEEXTENSIONSNAPACTION_H

#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"
#include <qlist.h>
#include <qobject.h>

class ShExtensionStartPoint {

	friend class ShDisposableExtensionSnapAction;

private:
	QList<ShEntity*> baseEntities;
	ShPoint3d point;

public:
	ShExtensionStartPoint();
	~ShExtensionStartPoint();

	ShExtensionStartPoint& operator=(const ShExtensionStartPoint &other);

private:
	void draw(QPainter *painter, ShCADWidget *widget);
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

class ShEnabledExtensionPoints {

	friend class ShDisposableExtensionSnapAction;

private:
	QList<ShEntity*> baseEntities;
	QList<ShPoint3d> extensionStartPoints;
	QList<ShPoint3d> extensionFinalPoints;

private:

	ShEnabledExtensionPoints();
	~ShEnabledExtensionPoints();

	void clear();
	inline int getCount() const { return this->baseEntities.count(); }
	void updateFinalSnap(const ShPoint3d &point, ShPoint3d &snap);

private:
	void draw(QPainter *painter, ShCADWidget *widget);
};


class ShDisposableExtensionSnapAction : public ShDisposableSnapAction, public QObject {
	
private:
	QList<ShExtensionStartPoint> extensionStartPoints;
	ShLastDeletePoint lastDeletePoint;
	ShLastAddedPoint lastAddedPoint;
	ShEnabledExtensionPoints enabledExtensionPoints;

public:
	ShDisposableExtensionSnapAction(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child = nullptr);
	~ShDisposableExtensionSnapAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual void draw(QPainter *painter);
	virtual void invalidate(ShDecoratorActionData &data);

protected:
	void updateExtensionStartPoints(const ShPoint3d &point);
	bool updateEnabledExtensionPoints(const ShPoint3d &point);

	private slots:
	void initializeLastDeletePoint();
	void initializeLastAddedPoint();

private:
	void searchEntities(const ShPoint3d &point, QLinkedList<ShEntity*> &foundEntities);
	bool findClosestVertexEndAndStart(const ShPoint3d &point, const QLinkedList<ShEntity*> &foundEntities, ShPoint3d &vertexPoint);
	bool checkAlreadyExistThenRemove(const ShPoint3d &point, const ShPoint3d &vertexPoint);
	void addMathchedVertexEntity(const ShPoint3d &point, const ShPoint3d &vertexPoint);
};

#endif //_SHDISPOSABLEEXTENSIONSNAPACTION_H