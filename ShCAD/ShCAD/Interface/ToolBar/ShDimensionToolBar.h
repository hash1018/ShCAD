

#ifndef _SHDIMENSIONTOOLBAR_H
#define _SHDIMENSIONTOOLBAR_H

#include "ShAbstractToolBar.h"
#include "Base\ShDimensionStyle.h"

class ShNotifyEvent;
class ShDimensionStyleComboBox;
class QPushButton;

class ShDimensionToolBar : public ShAbstractToolBar {

	Q_OBJECT

private:
	ShDimensionStyleComboBox *dimensionStyleComboBox;
	QPushButton *modifyDimensionStyleButton;

public:
	ShDimensionToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShDimensionToolBar();

public:
	void update(ShNotifyEvent *event);

	inline ShDimensionStyleComboBox* getDimensionStyleComboBox() const { return this->dimensionStyleComboBox; }
	

private:

	private slots :
	void dimLinearActionClicked();
	void dimAlignedActionClicked();
	void dimAngularActionClicked();
	void dimRadiusActionClicked();
	void dimDiameterActionClicked();
	void dimArcLengthActionClicked();

	void currentDimensionStyleChanged(ShDimensionStyle *dimensionStyle);
	void modifyDimensionStyleButtonClicked();

};

#endif //_SHDIMENSIONTOOLBAR_H