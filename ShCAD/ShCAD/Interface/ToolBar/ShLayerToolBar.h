
#ifndef _SHLAYERTOOLBAR_H
#define _SHLAYERTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShNotifyEvent;

class ShLayerToolBar : public ShAbstractToolBar {
	Q_OBJECT

public:
	ShLayerToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShLayerToolBar();

	void update(ShNotifyEvent *event);
};

#endif //_SHLAYERTOOLBAR_H