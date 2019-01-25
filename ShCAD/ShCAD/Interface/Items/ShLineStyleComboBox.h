

#ifndef _SHLINESTYLECOMBOBOX_H
#define _SHLINESTYLECOMBOBOX_H

#include <qcombobox.h>
#include "ShPropertyData.h"

class ShLineStyleComboBox : public QComboBox {
	Q_OBJECT

private:
	ShLineStyle blockLineStyle;
	ShLineStyle layerLineStyle;
	bool comboSelChangedByUser;
	int comboIndex;

public:
	ShLineStyleComboBox(QWidget *parent = 0);
	~ShLineStyleComboBox();
	void Synchronize(int index);
	void SetBlockLineStyle(const ShLineStyle& blockLineStyle);
	void SetLayerLineStyle(const ShLineStyle& layerLineStyle);

	inline int GetLineStyleComboIndex() const { return this->comboIndex; }

private:
	void SetComboCurrentIndex(int index);
	void UpdateLineStyleCombo();

	private slots:
	void LineStyleComboIndexChanged(int);

signals:
	void LineStyleChanged(const ShLineStyle& lineStyle);
};

#endif //_SHLINESTYLECOMBOBOX_