#ifndef SHCAD_H
#define SHCAD_H

#include <QtWidgets/QMainWindow>
class QMdiSubWindow;
class ShCommandDock;
class QMdiArea;
class QMenu;
class ShMenuBar;
class ShRibbonMenu;
class ShCAD : public QMainWindow
{
	Q_OBJECT

private:
	QMenu *contextMenu;

	ShCommandDock *commandDock;
	QMdiArea *mdiArea;
	ShMenuBar *menuBar;
	ShRibbonMenu *ribbonMenu;

public:
	ShCAD(QWidget *parent = nullptr);
	~ShCAD();

	void initWidgets();
	void registerWidgets();
	void activateWidgets();
	void deactivateWidgets();
	void createCADWidget();

private:
	void createContextMenu();

protected:
	bool eventFilter(QObject *obj, QEvent *event);

	private slots:
	void subActivateWindowChanged(QMdiSubWindow*);
	void showContexMenu(const QPoint &pos);
};

#endif // SHCAD_H
