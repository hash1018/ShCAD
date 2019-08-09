

#ifndef _SHOBJECTSNAPTOOLBAR_H
#define _SHOBJECTSNAPTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShObjectSnapToolBar : public ShAbstractToolBar {

public:
	ShObjectSnapToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShObjectSnapToolBar();


	private slots :

	void temporaryTrackPointClicked();
	void endPointClicked();
	void midPointClicked();
	void intersectionPointClicked();
	void apparentIntersectionPointClicked();
	void extensionPointClicked();
	void centerPointClicked();
	void quadrantPointClicked();
	void tangentPointClicked();
	void perpendicularClicked();

};

#endif //_SHOBJECTSNAPTOOLBAR_H