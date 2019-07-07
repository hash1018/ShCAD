
#ifndef _SHLAYERTOOLBAR_H
#define _SHLAYERTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShLayerToolBar : public ShAbstractToolBar {
	Q_OBJECT

public:
	ShLayerToolBar(const QString &title, QWidget *parent = nullptr);
	~ShLayerToolBar();

};

#endif //_SHLAYERTOOLBAR_H