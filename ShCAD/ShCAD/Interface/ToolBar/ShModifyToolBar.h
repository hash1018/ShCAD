

#ifndef _SHMODIFYTOOLBAR_H
#define _SHMODIFYTOOLBAR_H

#include "ShAbstractToolBar.h"
class ShModifyToolBar : public ShAbstractToolBar {

public:
	ShModifyToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShModifyToolBar();


	
	private slots:
	void eraseActionClicked();
	void copyActionClicked();
	void mirrorActionClicked();
	void offsetActionClicked();
	void moveActionClicked();
	void rotateActionClicked();
	void scaleActionClicked();
	void stretchActionClicked();
	void extendActionClicked();
	void trimActionClicked();
	
};

#endif //_SHMODIFYTOOLBAR_H