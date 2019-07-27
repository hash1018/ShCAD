

#ifndef _SHCADWidget_H
#define _SHCADWidget_H

#include <qopenglwidget.h>
#include "Data\ShPoint.h"
#include "Interface\Private\ShAxis.h"
#include "Base\ShVariable.h"
#include "Data\ShScrollPosition.h"
#include "UnRedo\ShTransactionStack.h"
#include "Data\ShDrawBuffer.h"
#include "Data\ShCommandLog.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
#include "Entity\Composite\ShEntityTable.h"
#include "Data\DraftData.h"

class ShNotifyEvent;
class ShActionHandler;
class ShTemporaryAction;
class ShActionHandlerProxy;
class ShChangeActionStrategy;

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
	DraftData draftData;
	

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

	//returns current orthMode.
	bool setOrthMode();

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

public:
	inline ShPoint3d getCoordinate() const { return this->coordinate; }
	inline ShScrollPosition getScrollPosition() const { return this->scroll; }
	inline double getZoomRate() const { return this->zoomRate; }
	inline ShAxis& getAxis() const { return const_cast<ShAxis&>(this->axis); }
	inline ShDrawBuffer& getDrawBuffer() const { return const_cast<ShDrawBuffer&>(this->drawBuffer); }
	inline const QImage& getCapturedImage() const { return const_cast<QImage&>(this->capturedImage); }
	inline ShActionHandlerProxy* getActionHandlerProxy() const { return this->actionHandlerProxy; }
	inline ShTransactionStack* getRedoStack() const { return this->redoStack; }
	inline ShTransactionStack* getUndoStack() const { return this->undoStack; }
	inline ShCommandLog& getCommandLog() const { return const_cast<ShCommandLog&>(this->commandLog); }
	inline ShRubberBand& getRubberBand() const { return const_cast<ShRubberBand&>(this->rubberBand); }
	inline ShEntityTable& getEntityTable() const { return const_cast<ShEntityTable&>(this->entityTable); }
	inline ShPreview& getPreview() const { return const_cast<ShPreview&>(this->preview); }
	inline DraftData& getDraftData() const { return const_cast<DraftData&>(this->draftData); }

};

#endif //_SHCADWIDGET_H