
#ifndef _SHMODIFYTOOLBAR_H
#define _SHMODIFYTOOLBAR_H

#include "ShAbstractToolBar.h"
class ShModifyToolBar : public ShAbstractToolBar {

public:
	ShModifyToolBar(const QString &title, QWidget *parent = 0);
	~ShModifyToolBar();


	private slots:
	void EraseActionClicked();
	void CopyActionClicked();
	void MirrorActionClicked();
	void MoveActionClicked();
	void RotateActionClicked();
	void ScaleActionClicked();
	void StretchActionClicked();
	void ExtendActionClicked();
	void TrimActionClicked();
};

#endif //_SHMODIFYTOOLBAR_H