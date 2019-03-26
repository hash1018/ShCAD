

#ifndef _SHSELECTIONMOVER_H
#define _SHSELECTIONMOVER_H

#include "ShVisitor.h"
#include "ShVariable.h"
#include "ShPoint.h"
#include <qlist.h>

class ShEntity;
class ShStretchData {
	
protected:
	ShStretchData();

public:
	virtual ~ShStretchData() = 0;

	
};

class ShStretchLeafData : public ShStretchData {
	friend class ShFindEntityToStretchVisitor;
	friend class ShFindStretchMovePointVisitor;
	friend class ShFindStretchPointWithRectVisitor;
	friend class ShStretchVisitor;

private:
	StretchPoint stretchPoint;

protected:
	ShStretchLeafData(StretchPoint stretchPoint);
	~ShStretchLeafData();

};

class ShStretchCompositeData : public ShStretchData {
	friend class ShFindEntityToStretchVisitor;
	friend class ShFindStretchMovePointVisitor;
	friend class ShFindStretchPointWithRectVisitor;
	friend class ShStretchVisitor;

private:
	StretchPoint stretchPoint;
	QList<int> childIndex;
	QList<ShStretchData*> childStretchData;
protected:
	ShStretchCompositeData();
	~ShStretchCompositeData();

};


class ShStretchVisitor : public ShVisitor {

private:
	ShPoint3d base;
	ShPoint3d current;
	ShEntity *original;
	ShStretchData *stretchData;
public:
	ShStretchVisitor(const ShPoint3d& base, const ShPoint3d& current);
	~ShStretchVisitor();
	
	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);

	void SetOriginal(ShEntity *original) { this->original = original; }
	void SetStretchData(ShStretchData *stretchData) { this->stretchData = stretchData; }

};


class ShFindEntityToStretchVisitor : public ShVisitor {

private:
	ShPoint3d point;
	QList<ShEntity*> &entitiesToStretch;
	QList<ShStretchData*> &stretchDataList;

public:
	ShFindEntityToStretchVisitor(const ShPoint3d& point, QList<ShEntity*> &entitiesToStretch,
		QList<ShStretchData*> &stretchDataList);
	~ShFindEntityToStretchVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);

};


class ShFindStretchMovePointVisitor : public ShVisitor {

private:
	QList<ShEntity*> &entitiesToStretch;
	QList<ShStretchData*> &stretchDataList;

public:
	ShFindStretchMovePointVisitor(QList<ShEntity*> &entitiesToStretch,
		QList<ShStretchData*> &stretchDataList);
	~ShFindStretchMovePointVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);

};



class ShFindStretchPointWithRectVisitor : public ShVisitor {

private:
	QList<ShEntity*> &entitiesToStretch;
	QList<ShStretchData*> &stretchDataList;
	ShPoint3d topLeft;
	ShPoint3d bottomRight;

public:
	ShFindStretchPointWithRectVisitor(QList<ShEntity*> &entitiesToStretch,
		QList<ShStretchData*> &stretchDataList, const ShPoint3d& topLeft, const ShPoint3d& bottomRight);
	~ShFindStretchPointWithRectVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);

};




class ShArrangePolyLineChildAfterStretchingVisitor : public ShVisitor {

private:
	ShEntity *entityToArrange;
	bool isPrevious;

public:
	ShArrangePolyLineChildAfterStretchingVisitor(ShEntity *entityToArrange, bool isPrevious = true);
	~ShArrangePolyLineChildAfterStretchingVisitor();

	virtual void Visit(ShLine *stretchedLine);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *stretchedArc);

};

class ShArrangePolyLineChildStretchedLineVisitor : public ShVisitor {
	friend class ShArrangePolyLineChildAfterStretchingVisitor;

private:
	ShLine *stretchedLine;
	bool isPrevious;

private:
	ShArrangePolyLineChildStretchedLineVisitor(ShLine *stretchedLine, bool isPrevious = true);
	~ShArrangePolyLineChildStretchedLineVisitor();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);

};

#endif //_SHSELECTIONMOVER_H