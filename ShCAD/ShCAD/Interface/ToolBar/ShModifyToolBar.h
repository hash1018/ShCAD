

#ifndef _SHMODIFYTOOLBAR_H
#define _SHMODIFYTOOLBAR_H

#include "ShAbstractToolBar.h"
class ShModifyToolBar : public ShAbstractToolBar {

public:
	ShModifyToolBar(const QString &title, QWidget *parent = nullptr);
	~ShModifyToolBar();


	
	private slots:
	void eraseActionClicked();
	void copyActionClicked();
	void mirrorActionClicked();
	void moveActionClicked();
	void rotateActionClicked();
	void scaleActionClicked();
	void stretchActionClicked();
	void extendActionClicked();
	void trimActionClicked();
};

#endif //_SHMODIFYTOOLBAR_H