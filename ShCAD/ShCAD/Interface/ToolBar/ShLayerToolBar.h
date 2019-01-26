

#ifndef _SHLAYERTOOLBAR_H
#define _SHLAYERTOOLBAR_H

#include <qtoolbar.h>
class ShLayerComboBox;
class ShActivatedWidgetChangedEvent;
class ShLayerToolBar : public QToolBar {

private:
	ShLayerComboBox *layerCombo;

public:
	ShLayerToolBar(QWidget *parent = 0);
	~ShLayerToolBar();

	void Update(ShActivatedWidgetChangedEvent *event);

};

#endif //_SHLAYERTOOLBAR_H