

#ifndef _SHOBJECTSNAPTOOLBAR_H
#define _SHOBJECTSNAPTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShObjectSnapToolBar : public ShAbstractToolBar {

public:
	ShObjectSnapToolBar(const QString &title, QWidget *parent = 0);
	~ShObjectSnapToolBar();

private:
	

	private slots:
	void TemporaryTrackPointClicked();
	void EndPointClicked();
	void MidPointClicked();
	void IntersectionPointClicked();
	void ApparentIntersectionPointClicked();
	void ExtensionPointClicked();
	void CenterPointClicked();
	void QuadrantPointClicked();
	void TangentPointClicked();
	void PerpendicularClicked();

};

#endif //_SHOBJECTSNAPTOOLBAR_H