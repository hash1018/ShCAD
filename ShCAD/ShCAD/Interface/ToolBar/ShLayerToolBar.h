

#ifndef _SHLAYERTOOLBAR_H
#define _SHLAYERTOOLBAR_H

#include <qtoolbar.h>
class ShLayerComboBox;
class ShActivatedWidgetChangedEvent;
class ShCurrentActionChangedEvent;
class ShNotifyEvent;
class QPushButton;
class ShLayer;
class ShColor;
class ShLayerToolBar : public QToolBar {
	Q_OBJECT
private:
	QPushButton *layerButton;
	ShLayerComboBox *layerCombo;

public:
	ShLayerToolBar(QWidget *parent = 0);
	~ShLayerToolBar();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Update(ShCurrentActionChangedEvent *event);
	void Notify(ShNotifyEvent *event);
	void SynchronizeLayerCombo();

	private slots:
	void CurrentLayerChanged(ShLayer* previousLayer, ShLayer *currentLayer);
	void LayerTurnChanged(ShLayer*, bool previous);
	void LayerColorChanged(ShLayer*, const ShColor& previous);
	void LayerButtonClicked();
};

#endif //_SHLAYERTOOLBAR_H