
#ifndef _SHCOMMANDDOCK_H
#define _SHCOMMANDDOCK_H

#include <qwidget.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qdockwidget.h>

class ShCommandList : public QTextEdit {

	friend class ShCommandContainer;
private:
	ShCommandList(QWidget *parent = 0);
	~ShCommandList();
};

class ShCommandEdit : public QLineEdit {
	friend class ShCommandContainer;
private:
	ShCommandEdit(QWidget *parent = 0);
	~ShCommandEdit();

};

class ShCommandContainer : public QWidget {
	friend class ShCommandDock;
private:
	ShCommandEdit *edit;
	ShCommandList *list;
	
private:
	ShCommandContainer(QWidget *parent = 0);
	~ShCommandContainer();

protected:
	void resizeEvent(QResizeEvent *event);

};

class ShCommandDock : public QDockWidget {

private:
	ShCommandContainer *container;

public:
	ShCommandDock(QWidget *parent = 0);
	~ShCommandDock();

protected:
	void closeEvent(QCloseEvent *event);

};

#endif //_SHCOMMANDWIDGET_H