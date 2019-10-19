
#ifndef _SHDIMENSIONSTYLECOMBOBOX_H
#define _SHDIMENSIONSTYLECOMBOBOX_H

#include <qcombobox.h>

class ShDimensionStyleTable;
class ShDimensionStyle;

class ShDimensionStyleComboBox : public QComboBox {
	Q_OBJECT

private:
	const ShDimensionStyleTable *dimensionStyleTable;
	bool dimensionStyleComboSelChangedByUser;
	int dimensionStyleComboIndex;

public:
	ShDimensionStyleComboBox(QWidget *parent = nullptr);
	~ShDimensionStyleComboBox();

public:
	void updateDimensionStyleCombo();
	void setDimensionStyleComboCurrentIndex(int index);
	void setDimensionStyleComboCurrentIndex(ShDimensionStyle *dimensionStyle);
	void setDimensionStyleTable(ShDimensionStyleTable *dimensionStyleTable) { this->dimensionStyleTable = dimensionStyleTable; }

public:
	inline int getDimensionStyleComboIndex() const { return this->dimensionStyleComboIndex; }

signals:
	void currentDimensionStyleChanged(ShDimensionStyle *dimensionStyle);

	private slots:
	void dimensionStyleComboIndexChanged(int index);

};


#endif //_SHDIMENSIONSTYLECOMBOBOX_H