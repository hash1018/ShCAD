

#include "ShActionHandler.h"

ShActionHandler::ShActionHandler(ShGraphicView *graphicView) {

	this->graphicView = graphicView;
}

ShActionHandler::~ShActionHandler() {


}

#include <qpainter.h>
QCursor ShActionHandler::GetCursorShape() {

	QPixmap pix(48, 48);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(QColor(255, 255, 255));

	painter.drawLine(24, 0, 24, 48);
	painter.drawLine(0, 24, 48, 24);

	painter.drawRect(21, 21, 6, 6);

	return QCursor(pix);
}


#include "Command Pattern\ShDeleteEntityCommand.h"
void ShActionHandler::DeleteSelectedEntities() {

	ShDeletedEntitiesMemento *memento = new ShDeletedEntitiesMemento;

	this->graphicView->selectedEntityManager.UnSelectAll();

	ShSelectedEntityManager::Iterator itr = this->graphicView->selectedEntityManager.GetJustUnSelectedBegin();

	while (!itr.IsEnd()) {
		memento->list.append(itr.Current()->CreateMemento());
		itr.Next();
	}

	ShDeleteEntityCommand *command = new ShDeleteEntityCommand(this->graphicView, memento);
	command->Execute();

	this->graphicView->undoTaker.Push(command);

	if (!this->graphicView->redoTaker.IsEmpty())
		this->graphicView->redoTaker.DeleteAll();

}