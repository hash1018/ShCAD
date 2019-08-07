#ifndef SHCAD_H
#define SHCAD_H

#include <QtWidgets/QMainWindow>
#include "Chain of Responsibility\ShChain.h"

class QMdiSubWindow;
class ShCommandDock;
class QMdiArea;
class QMenu;
class ShMenuBar;
class ShRibbonMenu;
class ShStatusBar;
class ShToolBarContainer;

class ShCAD : public QMainWindow, public ShChain {
	Q_OBJECT

private:
	QMenu *contextMenu;

	ShCommandDock *commandDock;
	QMdiArea *mdiArea;
	ShMenuBar *menuBar;
	ShRibbonMenu *ribbonMenu;
	ShStatusBar *statusBar;
	ShToolBarContainer *toolBarContainer;

public:
	ShCAD(QWidget *parent = nullptr);
	~ShCAD();

	void initWidgets();
	void registerWidgets();
	void activateWidgets();
	void deactivateWidgets();
	void createCADWidget();

	virtual void request(ShRequest *request);

private:
	void createContextMenu();

protected:
	bool eventFilter(QObject *obj, QEvent *event);

	private slots:
	void subActivateWindowChanged(QMdiSubWindow*);
	void showContexMenu(const QPoint &pos);
};

#endif // SHCAD_H
