
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/


#ifndef _SHGRAPHICVIEW_H
#define _SHGRAPHICVIEW_H

#include <qopenglwidget.h>
#include "ShVariable.h"
#include "Command Pattern\ShRedoTaker.h"
#include "Command Pattern\ShUndoTaker.h"
#include "Entity\Composite\ShPreview.h"
#include "Entity\Composite\ShEntityTable.h"
#include "ShSelectedEntityManager.h"
#include "ShAxis.h"
#include "ShPropertyData.h"
#include "ShDraft.h"

class ShRubberBand;
class ShActionHandlerManager;
class ShTemporaryAction;
class ShNotifyEvent;
class ShChangeCurrentActionStrategy;

class ShGraphicViewData {
	friend class ShGraphicView;
	
private:
	double x;
	double y;
	double z;
	double zoomRate;
	double hPos;
	double vPos;
	
	QString headTitle;
	QString edit;
	QString list;

	
	ShPropertyData layerData;
	ShPropertyData blockData;

	ShPropertyData propertyData;

public:
	ShGraphicViewData() :x(0), y(0), z(0), zoomRate(1), hPos(0), vPos(0), 
		headTitle(":: "), edit(""), list("") {
		propertyData.SetColor(ShColor(255, 255, 255, ShColor::Type::ByBlock));
		propertyData.SetLineStyle(ShLineStyle(0xFFFF, ShLineStyle::Type::ByBlock));
		
		blockData.SetColor(ShColor(255, 255, 255, ShColor::ByBlock));
		blockData.SetLineStyle(ShLineStyle(0xFFFF, ShLineStyle::ByBlock));
		
		layerData.SetColor(ShColor(255, 255, 255, ShColor::ByLayer));
		layerData.SetLineStyle(ShLineStyle(0xFFFF, ShLineStyle::ByLayer));
	}

	~ShGraphicViewData() {}

	inline QString GetHeadTitle() const { return this->headTitle; }
	inline QString GetEdit() const { return this->edit; }
	inline QString GetList() const { return this->list; }
	void SetHeadTitle(const QString& headTitle) { this->headTitle = headTitle; }
	void SetEdit(const QString& edit) { this->edit = edit; }
	void SetList(const QString& list) { this->list = list; }

	inline ShPropertyData* GetLayerData() { return &(this->layerData); }
	inline ShPropertyData* GetBlockData() { return &(this->blockData); }
	inline ShPropertyData* GetPropertyData() { return &(this->propertyData); }
	void SetLayerData(const ShPropertyData& layerData) { this->layerData = layerData; }
	void SetBlockData(const ShPropertyData& blockData) { this->blockData = blockData; }
	void SetPropertyData(const ShPropertyData& propertyData) { this->propertyData = propertyData; }

};


class ShGraphicView : public QOpenGLWidget {

private:
	ShGraphicViewData data;
	ShDraftFlag draftFlag;

public:

	/* class that maintains a container of entity object */
	ShEntityTable entityTable;

	//undo controller.
	ShUndoTaker undoTaker;
	//redo controller.
	ShRedoTaker redoTaker;

	ShSelectedEntityManager selectedEntityManager;

	DrawType drawType;
	QImage captureImage;
	//ShActionHandler *currentAction;
	ShActionHandlerManager *actionHandlerManager;

	ShRubberBand *rubberBand;
	ShPreview preview;
	ShAxis axis;

public:
	ShGraphicView(QWidget *parent = 0);
	~ShGraphicView();

	ActionType ChangeCurrentAction(ShChangeCurrentActionStrategy& strategy);
	virtual void update(DrawType drawType = DrawType::DrawAll);
	
	void CaptureImage();

	void Notify(ShNotifyEvent *event);
	void Update(ShNotifyEvent *event);

	void ConvertDeviceToEntity(int x, int y, double &ex, double &ey);
	void ConvertEntityToDevice(double x, double y, int &dx, int &dy);
	void MoveView(double ex, double ey, double zoomRate, int dx, int dy);
	void SetTemporaryAction(ShTemporaryAction *temporaryAction);
	void SetOrthogonalMode();
	void Print(QPainter *painter, double scale = 1.0);

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
	void SetHPos(int hPos) { this->data.hPos = hPos; }
	void SetVPos(int vPos) { this->data.vPos = vPos; }

	inline double GetX() const { return this->data.x; }
	inline double GetY() const { return this->data.y; }
	inline double GetZ() const { return this->data.z; }
	inline double GetZoomRate() const { return this->data.zoomRate; }
	inline double GetHPos() const { return this->data.hPos; }
	inline double GetVPos() const { return this->data.vPos; }

	inline ShGraphicViewData* GetData() { return &this->data; }
	ActionType GetCurrentActionType();

	inline ShDraftFlag GetDraftFlag() const { return this->draftFlag; }

	ShPoint3d GetCursorPoint();
	bool EnabledDrawEntityVertex();
};


#endif //_SHGRAPHICVIEW_H