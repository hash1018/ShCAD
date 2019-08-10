
#ifndef _SHQUICKACCESSTOOLBAR_H
#define _SHQUICKACCESSTOOLBAR_H

#include "ShAbstractToolBar.h"

class ShNotifyEvent;
class QPushButton;

class ShQuickAccessToolBar : public ShAbstractToolBar {

private:
	QPushButton *undoButton;
	QPushButton *redoButton;

public:
	ShQuickAccessToolBar(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShQuickAccessToolBar();

	void update(ShNotifyEvent *event);

	void setUndoButtonEnabled(bool enabled);
	void setRedoButtonEnabled(bool enabled);

	private slots :
	void newActionClicked();

};

#endif //_SHQUICKACCESSTOOLBAR_H