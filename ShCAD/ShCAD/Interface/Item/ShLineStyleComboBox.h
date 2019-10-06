
#ifndef _SHLINESTYLECOMBOBOX_H
#define _SHLINESTYLECOMBOBOX_H

#include <qcombobox.h>
#include "Data\ShLineStyle.h"

class ShLineStyleComboBox : public QComboBox {
	Q_OBJECT

private:
	ShLineStyle blockLineStyle;
	ShLineStyle layerLineStyle;

	bool lineStyleComboSelChangedByUser;
	int lineStyleComboIndex;

public:
	ShLineStyleComboBox(QWidget *parent = nullptr);
	~ShLineStyleComboBox();

	void setBlockLineStyle(const ShLineStyle &blockLineStyle);
	void setLayerLineStyle(const ShLineStyle &layerLineStyle);

	void updateLineStyleCombo();
	void setLineStyleComboCurrentIndex(int index);

	inline int getLineStyleComboIndex() const { return this->lineStyleComboIndex; }

signals:
	void lineStyleChanged(const ShLineStyle &lineStyle);

	private slots:
	void lineStyleComboIndexChanged(int index);

};

#endif //_SHLINESTYLECOMBOBOX_H