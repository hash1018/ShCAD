
#include "ShDragSelectAction.h"
#include <qpainter.h>
#include <QKeyEvent>
#include "KeyHandler\ShKeyHandler.h"
#include "Entity\Composite\ShSelectedEntities.h"
#include "Entity\Private\ShFinder.h"
#include "Entity\Private\ShStretchVisitor.h"
#include "Base\ShCursorShape.h"



//////////////////////////////////////////////////////


ShDragSelectAction::ShDragSelectAction(ShCADWidget *widget, double firstX, double firstY, Mode mode)
	:ShTemporaryAction(widget), firstX(firstX), firstY(firstY), mode(mode) {

	this->keyHandler = ShKeyHandler::ShBuilder(this->widget, this).
		allowKey(KeyType::Enter).
		allowKey(KeyType::Return).
		allowKey(KeyType::EscBackToPrevious).
		allowInput().
		build();
}

ShDragSelectAction::~ShDragSelectAction() {

}

void ShDragSelectAction::mouseLeftPressEvent(ShActionData &data) {

	QLinkedList<ShEntity*> searchedList;
	this->searchEntities(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY), searchedList);

	if (this->mode == Mode::SelectMode) {

		this->widget->getSelectedEntities()->add(searchedList);

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->widget->captureImage();

	}
	else if (this->mode == Mode::UnSelectMode) {

		this->widget->getSelectedEntities()->remove(searchedList);

		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();
	}

	shCommandLogManager->appendListEditTextWith("");

	this->returnToPrevious();
}

void ShDragSelectAction::mouseMoveEvent(ShActionData &data) {

	this->secondX = data.point.x;
	this->secondY = data.point.y;

	this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawActionHandler));
}


ActionType ShDragSelectAction::getType() {

	return ActionType::ActionTempDragSelect;
}

QCursor ShDragSelectAction::getCursorShape() {

	return ShCursorShape::getCursor(ShCursorShape::CursorType::Nothing);
}

QString ShDragSelectAction::getHeadTitle() {

	return shGetLanValue_command("Command/Specify opposite corner") + ": ";
}

void ShDragSelectAction::draw(QPainter *painter) {

	if (painter->isActive() == false)
		painter->begin(this->widget);


	SelectMethod selectMethod;
	ShPoint3d topLeft, bottomRight;
	this->getDragRectPoint(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY),
		topLeft, bottomRight, selectMethod);

	int topLeftX, topLeftY, bottomRightX, bottomRightY, width, height;
	this->widget->convertEntityToDevice(topLeft.x, topLeft.y, topLeftX, topLeftY);
	this->widget->convertEntityToDevice(bottomRight.x, bottomRight.y, bottomRightX, bottomRightY);
	width = abs(topLeftX - bottomRightX);
	height = abs(topLeftY - bottomRightY);


	QPen oldPen = painter->pen();
	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter->setPen(pen);


	if (selectMethod == SelectMethod::OnePart) {
		pen.setStyle(Qt::PenStyle::DotLine);
		painter->setPen(pen);
		painter->drawRect(topLeftX, topLeftY, width, height);
		painter->fillRect(topLeftX, topLeftY, width, height, QColor(102, 204, 102, 125));
	}
	else {
		painter->drawRect(topLeftX, topLeftY, width, height);
		painter->fillRect(topLeftX, topLeftY, width, height, QColor(102, 102, 204, 125));

	}


	painter->setPen(oldPen);
	painter->end();
}

void ShDragSelectAction::getDragRectPoint(const ShPoint3d &first, const ShPoint3d &second, ShPoint3d &topLeft, ShPoint3d &bottomRight, SelectMethod &selectMethod) {

	if (first.x > second.x && first.y > second.y) {
		selectMethod = OnePart;
		topLeft.x = second.x;
		topLeft.y = first.y;
		bottomRight.x = first.x;
		bottomRight.y = second.y;
	}
	else if (first.x <= second.x && first.y > second.y) {
		selectMethod = AllPart;
		topLeft.x = first.x;
		topLeft.y = first.y;
		bottomRight.x = second.x;
		bottomRight.y = second.y;
	}
	else if (first.x > second.x && first.y <= second.y) {
		selectMethod = OnePart;
		topLeft.x = second.x;
		topLeft.y = second.y;
		bottomRight.x = first.x;
		bottomRight.y = first.y;
	}
	else if (first.x <= second.x && first.y <= second.y) {
		selectMethod = AllPart;
		topLeft.x = first.x;
		topLeft.y = second.y;
		bottomRight.x = second.x;
		bottomRight.y = first.y;
	}
}

void ShDragSelectAction::searchEntities(const ShPoint3d &first, const ShPoint3d &second, QLinkedList<ShEntity*> &searchedList) {

	ShPoint3d topLeft, bottomRight;
	SelectMethod selectMethod;
	this->getDragRectPoint(first, second, topLeft, bottomRight, selectMethod);

	ShRectFinder::FindMethod findMethod;
	if (selectMethod == SelectMethod::AllPart)
		findMethod = ShRectFinder::AllPartLiesInsideRect;
	else
		findMethod = ShRectFinder::OnePartLiesInsideRect;

	ShEntity *entity = nullptr;
	ShRectFinder visitor(topLeft, bottomRight, &entity, findMethod);

	auto itr = this->widget->getEntityTable().turnOnLayerBegin();

	for (itr; itr != this->widget->getEntityTable().turnOnLayerEnd(); ++itr) {
	
		entity = nullptr;
		(*itr)->accept(&visitor);

		if (entity != nullptr)
			searchedList.append((*itr));
	}

}

int ShDragSelectAction::getAlreadySelectedCount(const QLinkedList<ShEntity*> &searchedList) {

	int count = 0;

	auto itr = const_cast<QLinkedList<ShEntity*>&>(searchedList).begin();
	
	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(searchedList).end(); ++itr) {

		if ((*itr)->isSelected() == true)
			count++;
	}

	return count;
}


//////////////////////////////////////////////////////////////////

ShModifyDragSelectAction::ShModifyDragSelectAction(ShCADWidget *widget, double firstX, double firstY, Mode mode)
	:ShDragSelectAction(widget, firstX, firstY, mode) {

}

ShModifyDragSelectAction::~ShModifyDragSelectAction() {

}

void ShModifyDragSelectAction::mouseLeftPressEvent(ShActionData &data) {

	QLinkedList<ShEntity*> searchedList;
	this->searchEntities(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY), searchedList);

	int searchedCount = searchedList.count();

	if (this->mode == Mode::SelectMode) {

		int duplicateCount = this->getAlreadySelectedCount(searchedList);

		this->widget->getSelectedEntities()->add(searchedList);
		int totalCount = this->widget->getSelectedEntities()->getSize();

		if (duplicateCount == 0)
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found, " +
				QString::number(totalCount) + " total");
		else
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found (" +
				QString::number(duplicateCount) + " duplicate), " + QString::number(totalCount) + " total");

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->widget->captureImage();

	}
	else if (this->mode == Mode::UnSelectMode) {

		int removedCount = this->getAlreadySelectedCount(searchedList);

		this->widget->getSelectedEntities()->remove(searchedList);
		int totalCount = this->widget->getSelectedEntities()->getSize();

		if (removedCount == 0)
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found, " +
				QString::number(totalCount) + " total");
		else
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found, " +
				QString::number(removedCount) + " removed, " + QString::number(totalCount) + " total");


		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();
	}

	this->returnToPrevious();
}

QString ShModifyDragSelectAction::getHeadTitle() {

	return this->previousAction->getHeadTitle() + ShDragSelectAction::getHeadTitle();
}


/////////////////////////////////////////////////////////////////////////////

ShModifyStretchDragSelectAction::ShModifyStretchDragSelectAction(ShCADWidget *widget, double firstX, double firstY,
	QLinkedList<ShEntity*> &possibleStretchEntities, QLinkedList<ShStretchData*> &stretchDatas, Mode mode)
	:ShModifyDragSelectAction(widget, firstX, firstY, mode), possibleStretchEntities(possibleStretchEntities),
	stretchDatas(stretchDatas) {

}

ShModifyStretchDragSelectAction::~ShModifyStretchDragSelectAction() {

}

void ShModifyStretchDragSelectAction::mouseLeftPressEvent(ShActionData &data) {

	QLinkedList<ShEntity*> searchedList;
	this->searchEntities(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY), searchedList);

	int searchedCount = searchedList.count();

	if (this->mode == Mode::SelectMode) {

		this->addStretchData(searchedList);

		int duplicateCount = this->getAlreadySelectedCount(searchedList);

		this->widget->getSelectedEntities()->add(searchedList);
		int totalCount = this->widget->getSelectedEntities()->getSize();

		if (duplicateCount == 0)
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found, " +
				QString::number(totalCount) + " total");
		else
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found (" +
				QString::number(duplicateCount) + " duplicate), " + QString::number(totalCount) + " total");

		this->widget->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawSelectedEntities));
		this->widget->captureImage();

	}
	else if (this->mode == Mode::UnSelectMode) {

		this->removeStretchData(searchedList);

		int removedCount = this->getAlreadySelectedCount(searchedList);

		this->widget->getSelectedEntities()->remove(searchedList);
		int totalCount = this->widget->getSelectedEntities()->getSize();

		if (removedCount == 0)
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found, " +
				QString::number(totalCount) + " total");
		else
			shCommandLogManager->appendListEditTextWith(QString::number(searchedCount) + " found, " +
				QString::number(removedCount) + " removed, " + QString::number(totalCount) + " total");


		this->widget->update(DrawType::DrawAll);
		this->widget->captureImage();
	}

	this->returnToPrevious();
}

void ShModifyStretchDragSelectAction::addStretchData(const QLinkedList<ShEntity*> &searchedEntities) {

	QLinkedList<ShEntity*> unSelectedEntities;

	auto itr = const_cast<QLinkedList<ShEntity*>&>(searchedEntities).begin();

	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(searchedEntities).end(); ++itr) {
	
		if ((*itr)->isSelected() == false)
			unSelectedEntities.append(*itr);
	}

	ShPoint3d topLeft, bottomRight;
	SelectMethod selectMethod;
	this->getDragRectPoint(ShPoint3d(this->firstX, this->firstY), ShPoint3d(this->secondX, this->secondY),
		topLeft, bottomRight, selectMethod);



	if (selectMethod == SelectMethod::AllPart) {
	
		ShStretchData *stretchData;
		ShStretchDataForMoveCreator visitor(&stretchData);

		itr = unSelectedEntities.begin();

		for (itr; itr != unSelectedEntities.end(); ++itr) {
		
			(*itr)->accept(&visitor);
			this->possibleStretchEntities.append(*itr);
			this->stretchDatas.append(stretchData);
		}
	}
	else {
	
		ShStretchData *stretchData;
		ShStretchPointRectFinder visitor(topLeft, bottomRight, &stretchData);

		itr = unSelectedEntities.begin();

		for (itr; itr != unSelectedEntities.end(); ++itr) {
		
			(*itr)->accept(&visitor);
			this->possibleStretchEntities.append(*itr);
			this->stretchDatas.append(stretchData);
		}
	}

}

void ShModifyStretchDragSelectAction::removeStretchData(const QLinkedList<ShEntity*> &searchedEntities) {

	QLinkedList<ShEntity*> selectedEntities;

	auto itr = const_cast<QLinkedList<ShEntity*>&>(searchedEntities).begin();

	for (itr; itr != const_cast<QLinkedList<ShEntity*>&>(searchedEntities).end(); ++itr) {

		if ((*itr)->isSelected() == true)
			selectedEntities.append(*itr);
	}

	itr = selectedEntities.begin();

	for (itr; itr != selectedEntities.end(); ++itr) {
	
		auto possibleStretchItr = this->possibleStretchEntities.begin();
		auto dataItr = this->stretchDatas.begin();
		
		for (possibleStretchItr; possibleStretchItr != this->possibleStretchEntities.end(); ++possibleStretchItr) {
		
			if (*possibleStretchItr == *itr) {
			
				this->possibleStretchEntities.removeOne(*possibleStretchItr);
				ShStretchData *stretchData = *dataItr;
				this->stretchDatas.removeOne(*dataItr);
				delete stretchData;
				break;
			}
			++dataItr;
		}
	}
}