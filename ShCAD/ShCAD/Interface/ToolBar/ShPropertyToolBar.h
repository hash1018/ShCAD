

#ifndef _SHPROPERTYTOOLBAR_H
#define _SHPROPERTYTOOLBAR_H

#include "ShAbstractToolBar.h"


class ShPropertyToolBar : public ShAbstractToolBar {
	Q_OBJECT

public:
	ShPropertyToolBar(const QString &title, QWidget *parent = nullptr);
	~ShPropertyToolBar();

};


#endif //_SHPROPERTYTOOLBAR_H