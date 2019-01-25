

#ifndef _SHCOLORCOMBOBOX_H
#define _SHCOLORCOMBOBOX_H

#include <qcombobox.h>
#include "ShPropertyData.h"

class ShColorComboBox : public QComboBox {
	Q_OBJECT

private:
	ShColor blockColor;
	ShColor layerColor;

	bool colorComboSelChangedByUser;
	int colorComboIndex;

public:
	ShColorComboBox(QWidget *parent);
	~ShColorComboBox();
	void Synchronize(int index);
	void OpenColorPickDialog();
	void SetBlockColor(const ShColor& blockColor);
	void SetLayerColor(const ShColor& layerColor);


	inline int GetColorComboIndex() const { return this->colorComboIndex; }

private:
	void SetColorComboCurrentIndex(int index);
	void UpdateColorCombo();
	

signals:
	void ColorChanged(const ShColor& color);

	private slots:
	void ColorComboIndexChanged(int);
};

#endif //_SHCOLORCOMBOBOX_H