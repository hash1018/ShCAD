
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
	
	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == 0)
		return;

	if (event->GetType() == ShNotifyEvent::Type::KeyPressed) {
	
		manager->GetActivatedWidget()->Update(event);
	}
}

void ShChangeManager::Notify(ShPropertyColumn *propertyColumn, ShNotifyEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == 0)
		return;

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {
		
		manager->GetActivatedWidget()->Update(event);
		this->propertyToolBar->SynchronizeColorCombo(dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event)->GetColor());
	}

	else if (event->GetType() == ShNotifyEvent::Type::PropertyLineStyleComboSelChanged) {
	
		manager->GetActivatedWidget()->Update(event);
		this->propertyToolBar->SynchronizeLineStyleCombo(dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event)->GetLineStyle());
	}
}

void ShChangeManager::Notify(ShPropertyToolBar *propertyToolBar, ShNotifyEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == 0)
		return;

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {
		
		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->SynchronizeColorCombo(dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event)->GetColor());
		
	}
	else if (event->GetType() == ShNotifyEvent::Type::PropertyLineStyleComboSelChanged) {
	
		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->SynchronizeLineStyleCombo(dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event)->GetLineStyle());
	}
}

void ShChangeManager::Notify(ShLayerToolBar *layerToolBar, ShNotifyEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == 0)
		return;

	if (event->GetType() == ShNotifyEvent::Type::LayerComboSelChanged) {
		manager->GetActivatedWidget()->Update(event);
		this->propertyToolBar->Update(dynamic_cast<ShLayerComboSelChangedEvent*>(event));
		this->propertyColumn->Update(dynamic_cast<ShLayerComboSelChangedEvent*>(event));
		this->layerColumn->SynchronizeLayerCombo(dynamic_cast<ShLayerComboSelChangedEvent*>(event)->GetIndex());

	}

	else if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {
	
		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->layerColumn->SynchronizeLayerCombo(this->layerToolBar->GetCurrentComboIndex());

	}
}


void ShChangeManager::Notify(ShLayerColumn *layerColumn, ShNotifyEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == 0)
		return;

	if (event->GetType() == ShNotifyEvent::Type::LayerComboSelChanged) {
		manager->GetActivatedWidget()->Update(event);
		this->propertyToolBar->Update(dynamic_cast<ShLayerComboSelChangedEvent*>(event));
		this->propertyColumn->Update(dynamic_cast<ShLayerComboSelChangedEvent*>(event));
		this->layerToolBar->SynchronizeLayerCombo(dynamic_cast<ShLayerComboSelChangedEvent*>(event)->GetIndex());
	}
	else if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {

		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->layerToolBar->SynchronizeLayerCombo(this->layerColumn->GetCurrentComboIndex());

	}
}

void ShChangeManager::Notify(ShLayerDialog *layerDialog, ShNotifyEvent *event) {

	ShWidgetManager *manager = ShWidgetManager::GetInstance();

	if (manager->GetActivatedWidget() == 0)
		return;

	if (event->GetType() == ShNotifyEvent::Type::LayerDataChanged) {
	
		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShLayerDataChangedEvent*>(event));

		int index = this->layerToolBar->GetCurrentComboIndex();
		this->layerToolBar->SynchronizeLayerCombo(index);
		this->layerColumn->SynchronizeLayerCombo(index);
	}
	else if (event->GetType() == ShNotifyEvent::Type::CurrentLayerChanged) {
	
		manager->GetActivatedWidget()->Update(event);
		this->propertyColumn->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));
		this->propertyToolBar->Update(dynamic_cast<ShCurrentLayerChangedEvent*>(event));

		

		if (dynamic_cast<ShCurrentLayerChangedEvent*>(event)->GetSelectedEntityCount() != 0) {
			int index = this->layerToolBar->GetCurrentComboIndex();
			this->layerToolBar->SynchronizeLayerCombo(index);
			this->layerColumn->SynchronizeLayerCombo(index);
		}
		else {
			this->layerColumn->SynchronizeLayerCombo();
			this->layerToolBar->SynchronizeLayerCombo();
		}
	

	}
	else if (event->GetType() == ShNotifyEvent::Type::LayerCreated) {
	
		manager->GetActivatedWidget()->Update(event);

		int index = this->layerToolBar->GetCurrentComboIndex();
		this->layerToolBar->SynchronizeLayerCombo(index);
		this->layerColumn->SynchronizeLayerCombo(index);
	}
	else if (event->GetType() == ShNotifyEvent::Type::LayerDeleted) {

		manager->GetActivatedWidget()->Update(event);

		int index = this->layerToolBar->GetCurrentComboIndex();
		this->layerToolBar->SynchronizeLayerCombo(index);
		this->layerColumn->SynchronizeLayerCombo(index);
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

void ShChangeManager::Notify(ShChangePropertyDataCommand *changePropertyDataCommand, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {
		ShPropertyColorComboSelChangedEvent *event2 = dynamic_cast<ShPropertyColorComboSelChangedEvent*>(event);

		this->propertyToolBar->SynchronizeColorCombo(event2->GetColor());
		this->propertyColumn->SynchronizeColorCombo(event2->GetColor());
	}
	else if (event->GetType() == ShNotifyEvent::Type::PropertyLineStyleComboSelChanged) {
	
		ShPropertyLineStyleComboSelChangedEvent *event2 = dynamic_cast<ShPropertyLineStyleComboSelChangedEvent*>(event);

		this->propertyToolBar->SynchronizeLineStyleCombo(event2->GetLineStyle());
		this->propertyColumn->SynchronizeLineStyleCombo(event2->GetLineStyle());

	}
}


void ShChangeManager::Notify(ShSelectedEntityManager *manager, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::SelectedEntityCountChanged) {
	
		this->propertyToolBar->Update(dynamic_cast<ShSelectedEntityCountChangedEvent*>(event));
		this->propertyColumn->Update(dynamic_cast<ShSelectedEntityCountChangedEvent*>(event));
		this->layerToolBar->Update(dynamic_cast<ShSelectedEntityCountChangedEvent*>(event));
		this->layerColumn->Update(dynamic_cast<ShSelectedEntityCountChangedEvent*>(event));

	}
}