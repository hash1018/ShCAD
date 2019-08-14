
#ifndef _SHLAYERTOOLBAR_H
#define _SHLAYERTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShNotifyEvent;
class ShLayerComboBox;
class ShColor;
class ShLayer;
class QPushButton;

class ShLayerToolBar : public ShAbstractToolBar {
	Q_OBJECT

private:
	QPushButton *layerButton;
	ShLayerComboBox *layerCombo;
	
public:
	ShLayerToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShLayerToolBar();

	void update(ShNotifyEvent *event);

	inline ShLayerComboBox* getLayerCombo() const { return this->layerCombo; }

	private slots:
	void currentLayerChanged(ShLayer *layer);
	void layerTurnChanged(ShLayer *layer, bool turnOn);
	void layerColorChanged(ShLayer *layer, const ShColor &color);
	void layerButtonClicked();
};

#endif //_SHLAYERTOOLBAR_H