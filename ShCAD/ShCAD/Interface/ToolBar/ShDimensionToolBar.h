

#ifndef _SHDIMENSIONTOOLBAR_H
#define _SHDIMENSIONTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShDimensionToolBar : public ShAbstractToolBar {

public:
	ShDimensionToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShDimensionToolBar();

private:

	private slots :
	void dimLinearActionClicked();
	void dimAlignedActionClicked();
	void dimAngularActionClicked();
	void dimRadiusActionClicked();
	void dimDiameterActionClicked();
	void dimArcLengthActionClicked();

};

#endif //_SHDIMENSIONTOOLBAR_H