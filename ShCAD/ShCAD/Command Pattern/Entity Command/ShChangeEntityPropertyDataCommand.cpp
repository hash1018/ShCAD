

#include "ShChangeEntityPropertyDataCommand.h"
#include "Entity\ShEntity.h"
#include "Interface\ShGraphicView.h"
ShChangeEntityPropertyDataCommand::ShChangeEntityPropertyDataCommand(ShGraphicView *view,
	const QLinkedList<ShEntity*>& selectedEntities, const QLinkedList<ShColor>& previousColors, const ShColor& color)
	:view(view), selectedEntities(selectedEntities), previousColors(previousColors),
	color(color), type(ChangedType::Color), ShCommand("Modify Entity Property") {

}

ShChangeEntityPropertyDataCommand::ShChangeEntityPropertyDataCommand(ShGraphicView *view,
	const QLinkedList<ShEntity*>& selectedEntities, const QLinkedList<ShLineStyle>& previousLineStyles,
	const ShLineStyle& lineStyle)
	: view(view), selectedEntities(selectedEntities), previousLineStyles(previousLineStyles)
	, lineStyle(lineStyle), type(ChangedType::LineStyle), ShCommand("Modify Entity Property") {

}

ShChangeEntityPropertyDataCommand::~ShChangeEntityPropertyDataCommand() {


}

void ShChangeEntityPropertyDataCommand::Execute() {
	qDebug("asdsdsad Execute");
	
	ShPropertyData data;
	
	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->selectedEntities.begin(); itr != this->selectedEntities.end(); ++itr) {

		data = (*itr)->GetPropertyData();

		if (this->type == ChangedType::Color) {

			if (this->color.GetType() == ShColor::Type::ByBlock)
				data.SetColor(this->view->GetData()->GetBlockData()->GetColor());
			else if (this->color.GetType() == ShColor::Type::ByLayer)
				data.SetColor((*itr)->GetLayer()->GetPropertyData().GetColor());
			else
				data.SetColor(this->color);

		}
		else if (this->type == ChangedType::LineStyle) {

			if (this->lineStyle.GetType() == ShLineStyle::Type::ByBlock)
				data.SetLineStyle(this->view->GetData()->GetBlockData()->GetLineStyle());
			else if (this->lineStyle.GetType() == ShLineStyle::Type::ByLayer)
				data.SetLineStyle((*itr)->GetLayer()->GetPropertyData().GetLineStyle());
			else
				data.SetLineStyle(this->lineStyle);

		}
		

		(*itr)->SetPropertyData(data);

	}


	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();
}

void ShChangeEntityPropertyDataCommand::UnExecute() {
	qDebug("asdsdsad UnExecute");

	ShPropertyData data;

	QLinkedList<ShEntity*>::iterator itr;

	if (this->type == ChangedType::Color) {
	
		QLinkedList<ShColor>::iterator itrColor = this->previousColors.begin();
		for (itr = this->selectedEntities.begin(); itr != this->selectedEntities.end(); ++itr) {

			data = (*itr)->GetPropertyData();
			data.SetColor((*itrColor));
			(*itr)->SetPropertyData(data);
			++itrColor;
		}

	}
	else if (this->type == ChangedType::LineStyle) {
	
		QLinkedList<ShLineStyle>::iterator itrLineStyle = this->previousLineStyles.begin();
		for (itr = this->selectedEntities.begin(); itr != this->selectedEntities.end(); ++itr) {

			data = (*itr)->GetPropertyData();
			data.SetLineStyle((*itrLineStyle));
			(*itr)->SetPropertyData(data);
			++itrLineStyle;
		}
	}



	this->view->update(DrawType::DrawAll);
	this->view->CaptureImage();

}