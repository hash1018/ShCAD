

#ifndef _SHLAYERTOOLBAR_H
#define _SHLAYERTOOLBAR_H

#include <qtoolbar.h>
class ShLayerComboBox;
class ShActivatedWidgetChangedEvent;
class ShNotifyEvent;
class QPushButton;
class ShLayer;
class ShLayerToolBar : public QToolBar {
	Q_OBJECT
private:
	QPushButton *layerButton;
	ShLayerComboBox *layerCombo;

public:
	ShLayerToolBar(QWidget *parent = 0);
	~ShLayerToolBar();

	void Update(ShActivatedWidgetChangedEvent *event);
	void Notify(ShNotifyEvent *event);
	void SynchronizeLayerCombo();

	private slots:
	void CurrentLayerChanged();
	void LayerTurnChanged(ShLayer*);
	void LayerColorChanged(ShLayer*);
	void LayerButtonClicked();
};

#endif //_SHLAYERTOOLBAR_H