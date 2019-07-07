#ifndef SHCAD_H
#define SHCAD_H

#include <QtWidgets/QMainWindow>
#include "ui_shcad.h"

class ShCAD : public QMainWindow
{
	Q_OBJECT

public:
	ShCAD(QWidget *parent = 0);
	~ShCAD();

private:
	Ui::ShCADClass ui;
};

#endif // SHCAD_H
