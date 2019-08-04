

#include "ShObjectSnapToolBar.h"
#include "Interface\Item\ShIcon.h"
#include "Manager\ShCADWidgetManager.h"
#include "Interface\ShCADWidget.h"
#include "Base\ShVariable.h"
#include "ActionHandler\Private\ShDecorateActionStrategy.h"

ShObjectSnapToolBar::ShObjectSnapToolBar(const QString &title, QWidget *parent)
	:ShAbstractToolBar(title, parent) {

	this->setIconSize(QSize(20, 20));

	QAction *action = this->addAction(ShIcon(":/Image/Snap/Temporary track point.png"), "Temporary track point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::temporaryTrackPointClicked);

	this->addSeparator();

	action = this->addAction(ShIcon(":/Image/Snap/End point.png"), "End point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::endPointClicked);

	action = this->addAction(ShIcon(":/Image/Snap/Mid point.png"), "Mid point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::midPointClicked);

	action = this->addAction(ShIcon(":/Image/Snap/Intersection point.png"), "Intersection point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::intersectionPointClicked);

	action = this->addAction(ShIcon(":/Image/Snap/Apparent intersection point.png"), "Apparent intersection point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::apparentIntersectionPointClicked);

	action = this->addAction(ShIcon(":/Image/Snap/Extension point"), "Extension point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::extensionPointClicked);

	this->addSeparator();

	action = this->addAction(ShIcon(":/Image/Snap/Center point.png"), "Center point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::centerPointClicked);

	action = this->addAction(ShIcon(":/Image/Snap/Quadrant point.png"), "Quadrant point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::quadrantPointClicked);

	action = this->addAction(ShIcon(":/Image/Snap/Tangent point.png"), "Tangent point");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::tangentPointClicked);

	this->addSeparator();

	action = this->addAction(ShIcon(":/Image/Snap/Perpendicular.png"), "Perpendicular");
	connect(action, &QAction::triggered, this, &ShObjectSnapToolBar::perpendicularClicked);

}

ShObjectSnapToolBar::~ShObjectSnapToolBar() {

}


void ShObjectSnapToolBar::temporaryTrackPointClicked() {


}


void ShObjectSnapToolBar::endPointClicked() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() != nullptr) {

		ShDecorateDisposableSnapActionStrategy strategy(ObjectSnap::ObjectSnapEndPoint);
		manager->getActivatedWidget()->changeAction(strategy);
	}
}

void ShObjectSnapToolBar::midPointClicked() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() != nullptr) {

		ShDecorateDisposableSnapActionStrategy strategy(ObjectSnap::ObjectSnapMidPoint);
		manager->getActivatedWidget()->changeAction(strategy);
	}
}


void ShObjectSnapToolBar::intersectionPointClicked() {


}

void ShObjectSnapToolBar::apparentIntersectionPointClicked() {

}

void ShObjectSnapToolBar::extensionPointClicked() {


}

void ShObjectSnapToolBar::centerPointClicked() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() != nullptr) {

		ShDecorateDisposableSnapActionStrategy strategy(ObjectSnap::ObjectSnapCenter);
		manager->getActivatedWidget()->changeAction(strategy);
	}
}

void ShObjectSnapToolBar::quadrantPointClicked() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() != nullptr) {

		ShDecorateDisposableSnapActionStrategy strategy(ObjectSnap::ObjectSnapQuadrant);
		manager->getActivatedWidget()->changeAction(strategy);
	}
}

void ShObjectSnapToolBar::tangentPointClicked() {


}

void ShObjectSnapToolBar::perpendicularClicked() {

	ShCADWidgetManager *manager = ShCADWidgetManager::getInstance();

	if (manager->getActivatedWidget() != nullptr) {

		ShDecorateDisposableSnapActionStrategy strategy(ObjectSnap::ObjectSnapPerpendicular);
		manager->getActivatedWidget()->changeAction(strategy);
	}
}