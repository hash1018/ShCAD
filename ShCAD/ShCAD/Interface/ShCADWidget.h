

#ifndef _SHCADWIDGET_H
#define _SHCADWIDGET_H

#include <qopenglwidget.h>
#include "Base\ShVariable.h"
#include "Data\ShPoint3d.h"
#include "Data\ShDrawBuffer.h"

class ShCADWidgetImp;
class ShChangeActionStrategy;
class ShActionHandlerProxy;
class ShTransactionStack;
class ShLayerTable;
class ShLayer;
class ShSelectedEntities;
class ShScrollPosition;
class ShPropertyData;
class ShAxis;
class ShDrawBuffer;
class ShCommandLog;
class ShRubberBand;
class ShEntityTable;
class ShPreview;
class ShDraftData;
class ShNotifyEvent;
class ShPointStyle;


class ShCADWidget : public QOpenGLWidget {
	
private:
	//Bridge Pattern.
	ShCADWidgetImp *widgetImp;
	ShDrawBuffer drawBuffer;
	QImage capturedImage;

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
	void plot(QPainter *painter, double scale);

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
	void setCoordinate(const ShPoint3d &coordinate);
	void setScrollPosition(const ShScrollPosition &scrollPosition);
	void setZoomRate(const double &zoomRate);
	void setPropertyData(const ShPropertyData &data);
	void setLastBasePoint(const ShPoint3d &point);

public:
	inline ShDrawBuffer& getDrawBuffer() const { return const_cast<ShDrawBuffer&>(this->drawBuffer); }
	inline const QImage& getCapturedImage() const { return this->capturedImage; }

public:
	const ShPoint3d& getCoordinate() const;
	const ShScrollPosition& getScrollPosition() const;
	const double& getZoomRate() const;
	ShAxis& getAxis() const;
	ShActionHandlerProxy* getActionHandlerProxy() const;
	ShTransactionStack* getRedoStack() const;
	ShTransactionStack* getUndoStack() const;
	ShCommandLog& getCommandLog() const;
	ShRubberBand& getRubberBand() const;
	ShEntityTable& getEntityTable() const;
	ShPreview& getPreview() const;
	ShDraftData& getDraftData();
	const ShPropertyData& getPropertyData() const;
	ShLayerTable* getLayerTable() const;
	ShLayer* getCurrentLayer() const;
	ShSelectedEntities* getSelectedEntities() const;
	ActionType getCurrentActionType() const;
	ShPointStyle& getPointStyle() const;
	const ShPoint3d& getLastBasePoint() const;

};

#endif //_SHCADWIDGET_H