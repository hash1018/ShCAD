

#ifndef _SHLAYERTOOLBAR_H
#define _SHLAYERTOOLBAR_H

#include "ShAbstractToolBar.h"
class ShLayerComboBox;
class ShActivatedWidgetChangedEvent;
class ShCurrentActionChangedEvent;
class ShSelectedEntityCountChangedEvent;
class ShNotifyEvent;
class QPushButton;
class ShLayer;
class ShColor;
class ShLayerToolBar : public ShAbstractToolBar {
	Q_OBJECT
private:
	QPushButton *layerButton;
	ShLayerComboBox *layerCombo;

public:
	ShLayerToolBar(const QString &title, QWidget *parent = 0);
	~ShLayerToolBar();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Update(ShCurrentActionChangedEvent *event);
	void Update(ShSelectedEntityCountChangedEvent *event);
	void Notify(ShNotifyEvent *event);
	void SynchronizeLayerCombo();
	void SynchronizeLayerCombo(int index);
	int GetCurrentComboIndex();

	private slots:
	void CurrentIndexChanged(int index);
	void LayerTurnChanged(ShLayer*, bool previous);
	void LayerColorChanged(ShLayer*, const ShColor& previous);
	void LayerButtonClicked();
};

#endif //_SHLAYERTOOLBAR_H