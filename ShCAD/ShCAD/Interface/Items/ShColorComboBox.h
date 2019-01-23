

#ifndef _SHCOLORCOMBOBOX_H
#define _SHCOLORCOMBOBOX_H

#include <qcombobox.h>
class ShColor;
class ShColorComboBox : public QComboBox {
	Q_OBJECT

private:
	bool colorComboSelChangedByUser;
	int colorComboIndex;

public:
	ShColorComboBox(QWidget *parent);
	~ShColorComboBox();
	void Synchronize(int index);
	inline int GetColorComboIndex() const { return this->colorComboIndex; }
	void OpenColorPickDialog();

private:
	void SetColorComboCurrentIndex(int index);
	void UpdateColorCombo();
	

signals:
	void ColorChanged(const ShColor& color);

	private slots:
	void ColorComboIndexChanged(int);
};

#endif //_SHCOLORCOMBOBOX_H