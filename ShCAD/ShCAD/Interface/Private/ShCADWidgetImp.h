

#ifndef _SHCADWIDGETIMP_H
#define _SHCADWIDGETIMP_H

//Bridge Pattern.

#include "Data\ShPoint3d.h"
#include "Interface\Private\ShAxis.h"
#include "Base\ShVariable.h"
#include "Data\ShScrollPosition.h"
#include "Data\ShCommandLog.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Data\ShDraftData.h"
#include "Data\ShPropertyData.h"
#include <qcursor.h>
#include "Base\ShPointStyle.h"
#include "Base\ShLastBasePoint.h"

class QMouseEvent;
class QKeyEvent;
class QWheelEvent;
class QFocusEvent;
class ShTransactionStack;
class ShActionHandlerProxy;
class ShSelectedEntities;
class ShChangeActionStrategy;

class ShCADWidgetImp {

	friend class ShCADWidget;

private:
	ShCADWidget *widget;

	ShPoint3d coordinate;
	double zoomRate;
	ShAxis axis;
	ShScrollPosition scroll;
	ShActionHandlerProxy *actionHandlerProxy;
	ShTransactionStack *undoStack;
	ShTransactionStack *redoStack;
	ShCommandLog commandLog;
	ShRubberBand rubberBand;
	ShEntityTable *entityTable;
	ShPreview preview;
	ShDraftData draftData;
	ShPropertyData propertyData;
	ShLayerTable *layerTable;
	ShSelectedEntities *selectedEntities;
	ShPointStyle pointStyle;
	ShLastBasePoint lastBasePoint;

private:
	ShCADWidgetImp(ShCADWidget *widget);
	~ShCADWidgetImp();

	void init();

	void changeAction(ShChangeActionStrategy &strategy);

	void convertDeviceToEntity(const int &x, const int &y, double &ex, double &ey);
	void convertEntityToDevice(const double &x, const double &y, int &dx, int &dy);

	void shiftViewport(const ShPoint3d &coordinate, int dx, int dy);

private:
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void wheelEvent(QWheelEvent *event);
	

private:
	void setCoordinate(const ShPoint3d &coordinate) { this->coordinate = coordinate; }
	void setScrollPosition(const ShScrollPosition &scrollPosition) { this->scroll = scrollPosition; }
	void setZoomRate(const double &zoomRate) { this->zoomRate = zoomRate; }
	void setPropertyData(const ShPropertyData &data) { this->propertyData = data; }
	void setLastBasePoint(const ShPoint3d &point) { this->lastBasePoint.setPoint(point); }

private:
	inline const ShPoint3d& getCoordinate() const { return this->coordinate; }
	inline const ShScrollPosition& getScrollPosition() const { return this->scroll; }
	inline const double& getZoomRate() const { return this->zoomRate; }
	inline ShAxis& getAxis() const { return const_cast<ShAxis&>(this->axis); }
	
	inline ShActionHandlerProxy* getActionHandlerProxy() const { return this->actionHandlerProxy; }
	inline ShTransactionStack* getRedoStack() const { return this->redoStack; }
	inline ShTransactionStack* getUndoStack() const { return this->undoStack; }
	inline ShCommandLog& getCommandLog() const { return const_cast<ShCommandLog&>(this->commandLog); }
	inline ShRubberBand& getRubberBand() const { return const_cast<ShRubberBand&>(this->rubberBand); }
	inline ShEntityTable& getEntityTable() const { return const_cast<ShEntityTable&>(*this->entityTable); }
	inline ShPreview& getPreview() const { return const_cast<ShPreview&>(this->preview); }
	inline ShDraftData& getDraftData() const { return const_cast<ShDraftData&>(this->draftData); }
	inline const ShPropertyData& getPropertyData() const { return this->propertyData; }
	inline ShLayerTable* getLayerTable() const { return this->layerTable; }
	ShLayer* getCurrentLayer() const;
	inline ShSelectedEntities* getSelectedEntities() const { return this->selectedEntities; }
	QCursor getCursorShape() const;
	ActionType getCurrentActionType() const;
	inline ShPointStyle& getPointStyle() const { return const_cast<ShPointStyle&>(this->pointStyle); }
	inline const ShPoint3d& getLastBasePoint() const { return this->lastBasePoint.getPoint(); }
};

#endif //_SHCADWIDGETIMP_H