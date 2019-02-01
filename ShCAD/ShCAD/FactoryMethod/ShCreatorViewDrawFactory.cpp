

#include "ShCreatorViewDrawFactory.h"
#include "Strategy Pattern\ShViewDrawStrategy.h"

ShCreatorViewDrawFactory::ShCreatorViewDrawFactory() {

}

ShCreatorViewDrawFactory::~ShCreatorViewDrawFactory() {

}

ShViewDrawStrategy* ShCreatorViewDrawFactory::Create(ShGraphicView *view, QPainter *painter, DrawType drawType) {

	if ((drawType & DrawType::DrawAll) == DrawType::DrawAll) {

		drawType = (DrawType)(drawType & ~DrawType::DrawAll);

		return new ShDrawAll(view, painter, drawType);

	}

	if ((drawType & DrawType::DrawCaptureImage) == DrawType::DrawCaptureImage) {

		drawType = (DrawType)(drawType & ~DrawType::DrawCaptureImage);

		return new ShDrawCaptureImage(view, painter, drawType);
	}

	if ((drawType & DrawType::DrawPreviewEntities) == DrawType::DrawPreviewEntities) {

		drawType = (DrawType)(drawType & ~DrawType::DrawPreviewEntities);

		return new ShDrawPreviewEntities(view, painter, drawType);
	}

	if ((drawType & DrawType::DrawAddedEntities) == DrawType::DrawAddedEntities) {
	
		drawType = (DrawType)(drawType & ~DrawType::DrawAddedEntities);

		return new ShDrawAddedEntities(view, painter, drawType);
	}

	if ((drawType & DrawType::DrawSelectedEntities) == DrawType::DrawSelectedEntities) {
	
		drawType = (DrawType)(drawType & ~DrawType::DrawSelectedEntities);

		return new ShDrawSelectedEntities(view, painter, drawType);
	}

	if ((drawType & DrawType::DrawJustUnSelectedEntities) == DrawType::DrawJustUnSelectedEntities) {
	
		drawType = (DrawType)(drawType & ~DrawType::DrawJustUnSelectedEntities);

		return new ShDrawJustUnSelectedEntities(view, painter, drawType);
	}

	if ((drawType & DrawType::DrawJustTurnOnLayer) == DrawType::DrawJustTurnOnLayer) {
	
		drawType = (DrawType)(drawType & ~DrawType::DrawJustTurnOnLayer);

		return new ShDrawJustTurnOnLayer(view, painter, drawType);
	}

	if ((drawType & DrawType::DrawActionHandler) == DrawType::DrawActionHandler) {
	
		drawType = (DrawType)(drawType & ~DrawType::DrawActionHandler);

		return new ShDrawActionHandler(view, painter, drawType);
	}



	return 0;
}

