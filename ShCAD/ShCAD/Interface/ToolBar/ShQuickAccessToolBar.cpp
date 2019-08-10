
#include "ShQuickAccessToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "Manager\ShLanguageManager.h"
#include "Chain of Responsibility\ShRequest.h"

ShQuickAccessToolBar::ShQuickAccessToolBar(const QString &title, ShChain *chain, QWidget *parent)
	:ShAbstractToolBar(title, chain, parent) {

	this->setObjectName("QuickAccessToolBar");

	this->setIconSize(QSize(20, 20));

	QAction *action = this->addAction(ShIcon(":/Image/File/New.png"), shGetLanValue_ui("File/New"));
	connect(action, &QAction::triggered, this, &ShQuickAccessToolBar::newActionClicked);

}

ShQuickAccessToolBar::~ShQuickAccessToolBar() {

}

void ShQuickAccessToolBar::newActionClicked() {

	ShCreateNewCADWidgetRequest request;
	this->request(&request);
}