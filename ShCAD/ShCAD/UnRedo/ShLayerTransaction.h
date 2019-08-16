
#ifndef _SHLAYERTRANSACTION_H
#define _SHLAYERTRANSACTION_H

#include "ShTransaction.h"
#include "Data\ShPropertyData.h"

class ShCADWidget;
class ShLayer;

class ShChangeCurrentLayerTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShLayer *prev;
	ShLayer *current;

public:
	ShChangeCurrentLayerTransaction(ShCADWidget *widget, ShLayer *prev, ShLayer *current);

	virtual void redo();
	virtual void undo();

protected:
	~ShChangeCurrentLayerTransaction();

};

/////////////////////////////////////////////

class ShChangeLayerDataTransaction : public ShTransaction {

public:
	enum ChangedType {
		Color,
		LineStyle,
		Name,
		Turn,
	};

private:
	ShCADWidget *widget;
	ShLayer *layer;
	ShPropertyData prev;
	ShPropertyData current;
	ChangedType changedType;
	QString prevName;
	QString currentName;
	bool prevTurn;
	bool currentTurn;

public:
	ShChangeLayerDataTransaction(ShCADWidget *widget, ShLayer *layer, const ShPropertyData &prev, const ShPropertyData &current, ChangedType changedType);
	ShChangeLayerDataTransaction(ShCADWidget *widget, ShLayer *layer, const QString &prev, const QString &current);
	ShChangeLayerDataTransaction(ShCADWidget *widget, ShLayer *layer, bool prevTurn, bool currentTurn);
	
	virtual void redo();
	virtual void undo();

protected:
	~ShChangeLayerDataTransaction();

private:
	void changeLayerColor(const ShPropertyData &aboutToChange);
	void changeLayerLineStyle(const ShPropertyData &aboutToChange);
	void changeLayerName(const QString &aboutToChange);
	void changeLayerTurn(const bool &aboutToChange);
};

///////////////////////////////////////////////////////////////////////

class ShCreateLayerTransaction : public ShTransaction {

private:
	ShLayer *layer;
	ShCADWidget *widget;
	bool mustDeleteLayer;

public:
	ShCreateLayerTransaction(ShCADWidget *widget, ShLayer *layer);
	
	virtual void redo();
	virtual void undo();

protected:
	~ShCreateLayerTransaction();

};

//////////////////////////////////////////////////////////////////////////

class ShDeleteLayerTransaction : public ShTransaction {

private:
	ShLayer *layer;
	ShCADWidget *widget;
	bool mustDeleteLayer;

public:
	ShDeleteLayerTransaction(ShCADWidget *widget, ShLayer *layer);

	virtual void redo();
	virtual void undo();

protected:
	~ShDeleteLayerTransaction();

};

#endif //_SHLAYERTRANSACTION_H