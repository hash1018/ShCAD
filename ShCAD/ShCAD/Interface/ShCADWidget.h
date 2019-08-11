

#ifndef _SHCADWIDGET_H
#define _SHCADWIDGET_H

#include <qopenglwidget.h>
#include "Data\ShPoint.h"
#include "Interface\Private\ShAxis.h"
#include "Base\ShVariable.h"
#include "Data\ShScrollPosition.h"
//#include "UnRedo\ShTransactionStack.h"
#include "Data\ShDrawBuffer.h"
#include "Data\ShCommandLog.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Data\ShDraftData.h"
#include "Data\ShPropertyData.h"

class ShNotifyEvent;
class ShActionHandler;
class ShTemporaryAction;
class ShActionHandlerProxy;
class ShChangeActionStrategy;
class ShTransactionStack;

class ShCADWidget : public QOpenGLWidget {
	
private:
	ShPoint3d coordinate;
	double zoomRate;
	ShAxis axis;
	ShScrollPosition scroll;
	ShDrawBuffer drawBuffer;
	QImage capturedImage;
	ShActionHandlerProxy *actionHandlerProxy;
	ShTransactionStack *undoStack;
	ShTransactionStack *redoStack;
	ShCommandLog commandLog;
	ShRubberBand rubberBand;
	ShEntityTable entityTable;
	ShPreview preview;
	ShDraftData draftData;
	ShPropertyData propertyData;
	

public:
	ShCADWidget(QWidget *parent = nullptr);
	~ShCADWidget();

	void notify(ShNotifyEvent *event);
	void update(ShNotifyEvent *event);
	
	void update(DrawType drawType = DrawType::DrawAll);

	void changeAction(ShChangeActionStrategy &strategy);

	void convertDeviceToEntity(const int &x, const int &y, double &ex, double &ey);
	void convertEntityToDevice(const double &x, const double &y, int &dx, int &dy);

	void captureImage();
	void shiftViewport(const ShPoint3d &coordinate, int dx, int dy);

	ShPoint3d getMousePoint();

protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int width, int height);

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void focusInEvent(QFocusEvent *event);


public:
	void setCoordinate(const ShPoint3d &coordinate) { this->coordinate = coordinate; }
	void setScrollPosition(const ShScrollPosition &scrollPosition) { this->scroll = scrollPosition; }
	void setZoomRate(const double &zoomRate) { this->zoomRate = zoomRate; }
	void setPropertyData(const ShPropertyData &data) { this->propertyData = data; }

public:
	inline ShPoint3d getCoordinate() const { return this->coordinate; }
	inline ShScrollPosition getScrollPosition() const { return this->scroll; }
	inline double getZoomRate() const { return this->zoomRate; }
	inline ShAxis& getAxis() const { return const_cast<ShAxis&>(this->axis); }
	inline ShDrawBuffer& getDrawBuffer() const { return const_cast<ShDrawBuffer&>(this->drawBuffer); }
	inline const QImage& getCapturedImage() const { return this->capturedImage; }
	inline ShActionHandlerProxy* getActionHandlerProxy() const { return this->actionHandlerProxy; }
	inline ShTransactionStack* getRedoStack() const { return this->redoStack; }
	inline ShTransactionStack* getUndoStack() const { return this->undoStack; }
	inline ShCommandLog& getCommandLog() const { return const_cast<ShCommandLog&>(this->commandLog); }
	inline ShRubberBand& getRubberBand() const { return const_cast<ShRubberBand&>(this->rubberBand); }
	inline ShEntityTable& getEntityTable() const { return const_cast<ShEntityTable&>(this->entityTable); }
	inline ShPreview& getPreview() const { return const_cast<ShPreview&>(this->preview); }
	inline ShDraftData& getDraftData() const { return const_cast<ShDraftData&>(this->draftData); }
	inline const ShPropertyData& getPropertyData() const { return this->propertyData; }

};

#endif //_SHCADWIDGET_H