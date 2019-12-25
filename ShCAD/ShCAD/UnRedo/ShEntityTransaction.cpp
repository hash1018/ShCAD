
#include "ShEntityTransaction.h"
#include "Entity\ShEntity.h"
#include "Interface\ShCADWidget.h"
#include "Entity\Private\Algorithm\ShMover.h"
#include "Entity\Private\Algorithm\ShRotater.h"
#include "Entity\Private\Algorithm\ShMirror.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Base\ShLayer.h"
#include "Entity\Composite\Dim\ShDim.h"
#include "Base\ShDimensionStyle.h"

ShAddEntityTransaction::ShAddEntityTransaction(ShCADWidget *widget, const QString &transactionName)
	:ShTransaction("Group " + transactionName), widget(widget), mustDeleteEntity(false) {

}

ShAddEntityTransaction::~ShAddEntityTransaction() {

	if (this->mustDeleteEntity == true) {
	
		while (!this->list.isEmpty())
			delete this->list.takeFirst();
	}
}


void ShAddEntityTransaction::redo() {

	this->widget->getEntityTable().add(this->list);
	this->mustDeleteEntity = false;

	this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->widget->captureImage();
}

void ShAddEntityTransaction::undo() {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		this->widget->getEntityTable().remove((*itr));


	this->mustDeleteEntity = true;

	this->widget->update();
	this->widget->captureImage();
}

void ShAddEntityTransaction::add(ShEntity *entity) {

	this->list.append(entity);
}

void ShAddEntityTransaction::add(const QLinkedList<ShEntity*> &list) {

	auto itr = const_cast<QLinkedList<ShEntity*>&>(list).begin();

	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(list).end(); ++itr)
		this->list.append((*itr));

}

//////////////////////////////////////////////////////////////////

ShMoveEntityTransaction::ShMoveEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list, double disX, double disY)
	:ShTransaction("Group Move"), widget(widget), list(list), disX(disX), disY(disY) {

}

ShMoveEntityTransaction::~ShMoveEntityTransaction() {

}

void ShMoveEntityTransaction::redo() {

	ShMover mover(this->disX, this->disY);

	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr)
		(*itr)->accept(&mover);

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShMoveEntityTransaction::undo() {

	ShMover mover(-this->disX, -this->disY);

	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr)
		(*itr)->accept(&mover);
	
	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

//////////////////////////////////////////////////////////////////////

ShRotateEntityTransaction::ShRotateEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list, const ShPoint3d &center, double angle)
	:ShTransaction("Group Rotate"), widget(widget), list(list), center(center), angle(angle) {

}

ShRotateEntityTransaction::~ShRotateEntityTransaction() {

}

void ShRotateEntityTransaction::redo() {

	ShRotater rotater(this->center, this->angle);

	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr)
		(*itr)->accept(&rotater);

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShRotateEntityTransaction::undo() {

	ShRotater rotater(this->center, -this->angle);

	auto itr = this->list.begin();

	for (itr; itr != this->list.end(); ++itr)
		(*itr)->accept(&rotater);

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

//////////////////////////////////////////////////////////////////////

ShMirrorEntityTransaction::ShMirrorEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list, const ShPoint3d &center, double angle)
	:ShTransaction("Group Mirror"), widget(widget), list(list), center(center), angle(angle) {

}

ShMirrorEntityTransaction::~ShMirrorEntityTransaction() {

}

void ShMirrorEntityTransaction::redo() {

	ShMirror mirror(this->center, this->angle);

	auto itr = this->list.begin();
	for (itr; itr != this->list.end(); ++itr) {
	
		mirror.setOriginal((*itr));
		(*itr)->accept(&mirror);
		
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShMirrorEntityTransaction::undo() {

	ShMirror mirror(this->center, this->angle);

	auto itr = this->list.begin();
	for (itr; itr != this->list.end(); ++itr) {

		mirror.setOriginal((*itr));
		(*itr)->accept(&mirror);
		
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

///////////////////////////////////////////////////////////

ShRemoveEntityTransaction::ShRemoveEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &list)
	:ShTransaction("Group Remove"), widget(widget), list(list), mustDeleteEntity(true) {

}

ShRemoveEntityTransaction::~ShRemoveEntityTransaction() {

	if (this->mustDeleteEntity == true) {

		while (!this->list.isEmpty())
			delete this->list.takeFirst();
	}
}

void ShRemoveEntityTransaction::redo() {

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		this->widget->getEntityTable().remove((*itr));


	this->mustDeleteEntity = true;

	this->widget->update();
	this->widget->captureImage();
}

void ShRemoveEntityTransaction::undo() {

	this->widget->getEntityTable().add(this->list);
	this->mustDeleteEntity = false;

	this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawAddedEntities));
	this->widget->captureImage();
}


////////////////////////////////////////////////////////////////


ShExtendEntityTransaction::ShExtendEntityTransaction(ShCADWidget *widget)
	:ShTransaction("Group Extend"), widget(widget), mustDeleteOriginal(true), mustDeleteExtended(false) {

}

ShExtendEntityTransaction::~ShExtendEntityTransaction() {

	if (this->mustDeleteOriginal == true) {
	
		while (!this->originalList.isEmpty())
			delete this->originalList.takeFirst();
	}

	if (this->mustDeleteExtended == true) {

		while (!this->extendedList.isEmpty())
			delete this->extendedList.takeFirst();
	}
}

void ShExtendEntityTransaction::redo() {

	this->widget->getEntityTable().add(this->extendedList);
	
	auto itr = this->originalList.begin();
	for (itr; itr != this->originalList.end(); ++itr)
		this->widget->getEntityTable().remove((*itr));

	this->mustDeleteOriginal = true;
	this->mustDeleteExtended = false;

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShExtendEntityTransaction::undo() {

	this->widget->getEntityTable().add(this->originalList);

	auto itr = this->extendedList.begin();
	for (itr; itr != this->extendedList.end(); ++itr)
		this->widget->getEntityTable().remove((*itr));

	this->mustDeleteOriginal = false;
	this->mustDeleteExtended = true;

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}


/////////////////////////////////////////////////////////////////////

ShTrimEntityTransaction::ShTrimEntityTransaction(ShCADWidget *widget)
	:ShTransaction("Group Trim"), widget(widget), mustDeleteOriginal(true), mustDeleteTrimed(false) {

}

ShTrimEntityTransaction::~ShTrimEntityTransaction() {

	if (this->mustDeleteOriginal == true) {

		while (!this->originalList.isEmpty())
			delete this->originalList.takeFirst();
	}

	if (this->mustDeleteTrimed == true) {

		while (!this->trimedList.isEmpty())
			delete this->trimedList.takeFirst();
	}
}

void ShTrimEntityTransaction::redo() {

	this->widget->getEntityTable().add(this->trimedList);

	auto itr = this->originalList.begin();
	for (itr; itr != this->originalList.end(); ++itr)
		this->widget->getEntityTable().remove((*itr));

	this->mustDeleteOriginal = true;
	this->mustDeleteTrimed = false;

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShTrimEntityTransaction::undo() {

	this->widget->getEntityTable().add(this->originalList);

	auto itr = this->trimedList.begin();
	for (itr; itr != this->trimedList.end(); ++itr)
		this->widget->getEntityTable().remove((*itr));

	this->mustDeleteOriginal = false;
	this->mustDeleteTrimed = true;

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}


///////////////////////////////////////////////////////////////


ShStretchEntityTransaction::ShStretchEntityTransaction(ShCADWidget *widget, const QLinkedList<ShEntity*> &originalEntities, const QLinkedList<ShEntity*> &stretchedEntities)
	:ShTransaction("Group Stretch"), widget(widget), originalEntities(originalEntities), stretchedEntities(stretchedEntities),
	mustDeleteOriginal(true), mustDeleteStretched(false) {

}

ShStretchEntityTransaction::~ShStretchEntityTransaction() {

	if (this->mustDeleteOriginal == true)
		while (!this->originalEntities.isEmpty())
			delete this->originalEntities.takeFirst();

	if (this->mustDeleteStretched == true)
		while (!this->stretchedEntities.isEmpty())
			delete this->stretchedEntities.takeFirst();
}

void ShStretchEntityTransaction::redo() {

	auto itr = this->stretchedEntities.begin();
	auto itr2 = this->originalEntities.begin();

	for (itr; itr != this->stretchedEntities.end(); ++itr) {

		this->widget->getEntityTable().remove((*itr2));
		this->widget->getEntityTable().add((*itr));
		++itr2;
	}

	this->mustDeleteOriginal = true;
	this->mustDeleteStretched = false;

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShStretchEntityTransaction::undo() {

	auto itr = this->stretchedEntities.begin();
	auto itr2 = this->originalEntities.begin();

	for (itr; itr != this->stretchedEntities.end(); ++itr) {

		this->widget->getEntityTable().remove((*itr));
		this->widget->getEntityTable().add((*itr2));
		++itr2;
	}

	this->mustDeleteOriginal = false;
	this->mustDeleteStretched = true;

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}


///////////////////////////////////////////////////////////////////////


ShChangeEntityPropertyDataTransaction::ShChangeEntityPropertyDataTransaction(ShCADWidget *widget)
	:ShTransaction("Change Property"), widget(widget) {

}

ShChangeEntityPropertyDataTransaction::~ShChangeEntityPropertyDataTransaction() {

}

void ShChangeEntityPropertyDataTransaction::redo() {

	auto itr = this->entities.begin();
	auto itrCurrent = this->current.begin();

	for (itr; itr != this->entities.end(); ++itr) {
	
		(*itr)->setPropertyData((*itrCurrent));
		++itrCurrent;
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShChangeEntityPropertyDataTransaction::undo() {

	auto itr = this->entities.begin();
	auto itrPrev = this->prev.begin();

	for (itr; itr != this->entities.end(); ++itr) {

		(*itr)->setPropertyData((*itrPrev));
		++itrPrev;
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShChangeEntityPropertyDataTransaction::add(ShEntity *entity, const ShPropertyData &prev, const ShPropertyData &current) {

	this->entities.append(entity);
	this->prev.append(prev);
	this->current.append(current);
}


////////////////////////////////////////////////////////////////////////

ShChangeEntityLayerTransaction::ShChangeEntityLayerTransaction(ShCADWidget *widget)
	:ShTransaction("Change Layer"), widget(widget) {

}

ShChangeEntityLayerTransaction::~ShChangeEntityLayerTransaction() {

}

void ShChangeEntityLayerTransaction::redo() {

	auto itr = this->entities.begin();
	auto itrCurrent = this->current.begin();

	ShPropertyData propertyData;

	for (itr; itr != this->entities.end(); ++itr) {
		
		(*itr)->getLayer()->remove(*itr);
		(*itr)->setLayer((*itrCurrent));
		(*itrCurrent)->add((*itr));

		propertyData = (*itr)->getPropertyData();

		if (propertyData.getColor().getType() == ShColor::Type::ByLayer)
			propertyData.setColor((*itrCurrent)->getPropertyData().getColor());
		if (propertyData.getLineStyle().getType() == ShLineStyle::Type::ByLayer)
			propertyData.setLineStyle((*itrCurrent)->getPropertyData().getLineStyle());

		(*itr)->setPropertyData(propertyData);
		++itrCurrent;
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShChangeEntityLayerTransaction::undo() {

	auto itr = this->entities.begin();
	auto itrPrev = this->prev.begin();

	ShPropertyData propertyData;

	for (itr; itr != this->entities.end(); ++itr) {

		(*itr)->getLayer()->remove(*itr);
		(*itr)->setLayer((*itrPrev));
		(*itrPrev)->add(*itr);

		propertyData = (*itr)->getPropertyData();

		if (propertyData.getColor().getType() == ShColor::Type::ByLayer)
			propertyData.setColor((*itrPrev)->getPropertyData().getColor());
		if (propertyData.getLineStyle().getType() == ShLineStyle::Type::ByLayer)
			propertyData.setLineStyle((*itrPrev)->getPropertyData().getLineStyle());

		(*itr)->setPropertyData(propertyData);
		++itrPrev;
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShChangeEntityLayerTransaction::add(ShEntity *entity, ShLayer *prev, ShLayer *current) {

	this->entities.append(entity);
	this->prev.append(prev);
	this->current.append(current);
}


////////////////////////////////////////////////////////////////

ShChangeDimDimensionStyleTransaction::ShChangeDimDimensionStyleTransaction(ShCADWidget *widget)
	:ShTransaction("Change DimensionStyle"), widget(widget) {

}

ShChangeDimDimensionStyleTransaction::~ShChangeDimDimensionStyleTransaction() {

}

void ShChangeDimDimensionStyleTransaction::redo() {

	auto itr = this->dims.begin();
	auto itrCurrent = this->current.begin();

	for (itr; itr != this->dims.end(); ++itr) {
	
		const_cast<ShDimensionStyle*>((*itr)->getDimensionStyle())->remove(*itr);
		(*itr)->setDimensionStyle(*itrCurrent);
		(*itrCurrent)->add(*itr);

		(*itr)->updateChild();

		++itrCurrent;
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShChangeDimDimensionStyleTransaction::undo() {

	auto itr = this->dims.begin();
	auto itrPrev = this->prev.begin();

	for (itr; itr != this->dims.end(); ++itr) {

		const_cast<ShDimensionStyle*>((*itr)->getDimensionStyle())->remove(*itr);
		(*itr)->setDimensionStyle(*itrPrev);
		(*itrPrev)->add(*itr);

		(*itr)->updateChild();

		++itrPrev;
	}

	this->widget->update(DrawType::DrawAll);
	this->widget->captureImage();
}

void ShChangeDimDimensionStyleTransaction::add(ShDim *dim, ShDimensionStyle *prev, ShDimensionStyle *current) {

	this->dims.append(dim);
	this->prev.append(prev);
	this->current.append(current);
}