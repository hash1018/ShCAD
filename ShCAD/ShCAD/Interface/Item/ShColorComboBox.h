
#ifndef _SHCOLORCOMBOBOX_H
#define _SHCOLORCOMBOBOX_H

#include <qcombobox.h>
#include "Data\ShColor.h"

class ShColorComboBox : public QComboBox {
	Q_OBJECT
private:
	ShColor blockColor;
	ShColor layerColor;

	bool colorComboSelChangedByUser;
	int colorComboIndex;

public:
	ShColorComboBox(QWidget *parent = nullptr);
	~ShColorComboBox();

	void openColorPickDialog();
	void setBlockColor(const ShColor &blockColor);
	void setLayerColor(const ShColor &layerColor);

	void updateColorCombo();
	void setColorComboCurrentIndex(int index);

	inline int getColorComboIndex() const { return this->colorComboIndex; }

signals:
	void colorChanged(const ShColor &color);

	private slots:
	void colorComboIndexChanged(int index);

};

#endif //_SHCOLORCOMBOBOX_H