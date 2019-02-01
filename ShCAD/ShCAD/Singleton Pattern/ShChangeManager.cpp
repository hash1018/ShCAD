
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#include "ShChangeManager.h"
#include "Interface\ShGraphicView.h"
#include "Interface\ShStatusBar.h"
#include "ShNotifyEvent.h"
#include "Interface\Dock\ShCommandDock.h"
#include "ShWidgetManager.h"
#include "Interface\Ribbon\ShHomeTab.h"
#include "Interface\ToolBar\ShPropertyToolBar.h"
#include "Interface\ToolBar\ShLayerToolBar.h"

ShChangeManager ShChangeManager::instance;

ShChangeManager::ShChangeManager() {

}

ShChangeManager::~ShChangeManager() {

}

ShChangeManager* ShChangeManager::GetInstance() {

	return &(ShChangeManager::instance);
}

void ShChangeManager::Register(ShStatusBar *statusBar) {

	this->statusBar = statusBar;
}

void ShChangeManager::Register(ShCommandDock *commandDock) {

	this->commandDock = commandDock;
}

void ShChangeManager::Register(ShPropertyColumn *propertyColumn) {

	this->propertyColumn = propertyColumn;
}

void ShChangeManager::Register(ShPropertyToolBar *propertyToolBar) {

	this->propertyToolBar = propertyToolBar;
}

void ShChangeManager::Register(ShLayerToolBar *layerToolBar) {

	this->layerToolBar = layerToolBar;
}

void ShChangeManager::Register(ShLayerColumn *layerColumn) {

	this->layerColumn = layerColumn;
}

void ShChangeManager::Notify(ShGraphicView *view, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::MousePositionChanged) {

		ShMousePositionChangedEvent *event2 = dynamic_cast<ShMousePositionChangedEvent*>(event);
		this->statusBar->Update(event2->GetX(), event2->GetY(), event2->GetZ(), event2->GetZoomRate());
	}
	else if (event->GetType() == ShNotifyEvent::Type::ZoomRateChanged) {

		ShZoomRateChangedEvent *event2 = dynamic_cast<ShZoomRateChangedEvent*>(event);
		this->statusBar->Update(event2->GetX(), event2->GetY(), event2->GetZ(), event2->GetZoomRate());

	}
	else if (event->GetType() == ShNotifyEvent::Type::KeyPressed)
		this->commandDock->Update(dynamic_cast<ShKeyPressedEvent*>(event));

	else if (event->GetType() == ShNotifyEvent::Type::UpdateListText)
		this->commandDock->Update(dynamic_cast<ShUpdateListTextEvent*>(event));
	

	else if (event->GetType() == ShNotifyEvent::Type::ActivatedWidgetChanged) {
	
		this->commandDock->Update(dynamic_cast<ShActivatedWidgetChangedEvent*>(event));
		this->propertyColumn->Update(dynamic_cast<ShActivatedWidgetChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShActivatedWidgetChangedEvent*>(event));
		this->layerToolBar->Update(dynamic_cast<ShActivatedWidgetChangedEvent*>(event));
		this->layerColumn->Update(dynamic_cast<ShActivatedWidgetChangedEvent*>(event));

	}

	else if (event->GetType() == ShNotifyEvent::Type::CurrentActionChanged) {
	
		this->propertyColumn->Update(dynamic_cast<ShCurrentActionChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShCurrentActionChangedEvent*>(event));
		this->layerToolBar->Update(dynamic_cast<ShCurrentActionChangedEvent*>(event));
		this->layerColumn->Update(dynamic_cast<ShCurrentActionChangedEvent*>(event));

	}



}


void ShChangeManager::Notify(ShCommandDock* commandDock, ShNotifyEvent *event) {
	
	if (event->GetType() == ShNotifyEvent::Type::KeyPressed) {
	
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);

	}

	
}

void ShChangeManager::Notify(ShPropertyColumn *propertyColumn, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {
		
		this->propertyToolBar->SynchronizeColorCombo(propertyColumn->GetColorComboIndex());

		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
		
	}

	else if (event->GetType() == ShNotifyEvent::Type::PropertyLineStyleComboSelChanged) {
	
		this->propertyToolBar->SynchronizeLineStyleCombo(propertyColumn->GetLineStyleComboIndex());

		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
	}

}

void ShChangeManager::Notify(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {

		this->propertyColumn->SynchronizeColorCombo(propertyToolBar->GetColorComboIndex());

		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);

	}
	else if (event->GetType() == ShNotifyEvent::Type::PropertyLineStyleComboSelChanged) {
	
		this->propertyColumn->SynchronizeLineStyleCombo(propertyToolBar->GetLineStyleComboIndex());

		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);

	}

}

void ShChangeManager::Notify(ShLayerToolBar *layerToolBar, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::CurrentLayerChanged) {

		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));

		this->layerColumn->SynchronizeLayerCombo();
	
	}
	else if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {
	
		//later add redraw when layer turns off

		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

		this->layerColumn->SynchronizeLayerCombo();
	}


}


void ShChangeManager::Notify(ShLayerColumn *layerColumn, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::CurrentLayerChanged) {

		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));

		this->layerToolBar->SynchronizeLayerCombo();

	}
	else if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {

		//later add redraw when layer turns off
	
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

		this->layerToolBar->SynchronizeLayerCombo();
		

	}

}

void ShChangeManager::Notify(ShLayerDialog *layerDialog, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {
	
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();
	}
	else if (event->GetType() == ShNotifyEvent::Type::CurrentLayerChanged) {
	
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();

	}
	else if (event->GetType() == ShNotifyEvent::Type::LayerCreated) {
	
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();
	}
	else if (event->GetType() == ShNotifyEvent::Type::LayerDeleted) {
	
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();
	}

}

void ShChangeManager::Notify(ShChangeCurrentLayerCommand *changeCurrentLayerCommand, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::CurrentLayerChanged) {
		this->propertyColumn->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();
	}
}

void ShChangeManager::Notfiy(ShChangeLayerDataCommand *changeLayerDataCommand, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::LayerDataChanged) {
	
		this->propertyColumn->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();
	}
}

void ShChangeManager::Notify(ShCreateLayerCommand *createLayerCommand, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::LayerCreated ||
		event->GetType() == ShNotifyEvent::LayerDeleted) {

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();
	}


}

void ShChangeManager::Notify(ShDeleteLayerCommand *deleteLayerCommand, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::LayerCreated ||
		event->GetType() == ShNotifyEvent::LayerDeleted) {

		this->layerToolBar->SynchronizeLayerCombo();
		this->layerColumn->SynchronizeLayerCombo();
	}

}