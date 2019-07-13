

#include "ShCADWidgetDrawStrategyFactory.h"
#include "ShCADWidgetDrawStrategy.h"

ShCADWidgetDrawStrategyFactory::ShCADWidgetDrawStrategyFactory() {

}

ShCADWidgetDrawStrategyFactory::~ShCADWidgetDrawStrategyFactory() {

}

ShCADWidgetDrawStrategy* ShCADWidgetDrawStrategyFactory::create(ShCADWidget *widget, QPainter *painter, DrawType drawType) {

	if ((drawType & DrawType::DrawAll) == DrawType::DrawAll) {

		drawType = (DrawType)(drawType & ~DrawType::DrawAll);

		return new ShDrawAllStrategy(widget, painter, drawType);

	}

	if ((drawType & DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage) {

		drawType = (DrawType)(drawType & ~DrawType::DrawCaptureImage);

		return new ShDrawCaptureImageStrategy(widget, painter, drawType);
	}

	if ((drawType & DrawType::DrawPreviewEntities) == DrawType::DrawPreviewEntities) {

		drawType = (DrawType)(drawType & ~DrawType::DrawPreviewEntities);

		return new ShDrawPreviewEntitiesStrategy(widget, painter, drawType);
	}

	if ((drawType & DrawType::DrawAddedEntities) == DrawType::DrawAddedEntities) {

		drawType = (DrawType)(drawType & ~DrawType::DrawAddedEntities);

		return new ShDrawAddedEntitiesStrategy(widget, painter, drawType);
	}

	if ((drawType & DrawType::DrawSelectedEntities) == DrawType::DrawSelectedEntities) {

		drawType = (DrawType)(drawType & ~DrawType::DrawSelectedEntities);

		return new ShDrawSelectedEntitiesStrategy(widget, painter, drawType);
	}



	if ((drawType & DrawType::DrawJustTurnOnLayer) == DrawType::DrawJustTurnOnLayer) {

		drawType = (DrawType)(drawType & ~DrawType::DrawJustTurnOnLayer);

		return new ShDrawJustTurnOnLayerStrategy(widget, painter, drawType);
	}

	if ((drawType & DrawType::DrawActionHandler) == DrawType::DrawActionHandler) {

		drawType = (DrawType)(drawType & ~DrawType::DrawActionHandler);

		return new ShDrawActionHandlerStrategy(widget, painter, drawType);
	}



	return nullptr;
}

