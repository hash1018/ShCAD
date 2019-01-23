

#ifndef _SHLINESTYLECOMBOBOX_H
#define _SHLINESTYLECOMBOBOX_H

#include <qcombobox.h>
class ShLineStyle;
class ShLineStyleComboBox : public QComboBox {
	Q_OBJECT

public:
	ShLineStyleComboBox(QWidget *parent = 0);
	~ShLineStyleComboBox();

private:
	void UpdateLineStyleCombo();

	private slots:
	void LineStyleComboIndexChanged(int);

signals:
	void LineStyleChanged(const ShLineStyle& lineStyle);
};

#endif //_SHLINESTYLECOMBOBOX_