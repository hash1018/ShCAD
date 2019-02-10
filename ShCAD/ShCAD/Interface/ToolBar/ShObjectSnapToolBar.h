

#ifndef _SHOBJECTSNAPTOOLBAR_H
#define _SHOBJECTSNAPTOOLBAR_H

#include <qtoolbar.h>

class ShObjectSnapToolBar : public QToolBar {

public:
	ShObjectSnapToolBar(QWidget *parent = 0);
	~ShObjectSnapToolBar();

private:
	void GetIcon(const QString& filePath, QIcon& icon);

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