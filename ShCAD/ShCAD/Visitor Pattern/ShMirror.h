

#ifndef _SHMIRROR_H
#define _SHMIRROR_H

#include "ShVisitor.h"
#include "ShPoint.h"
class ShEntity;
class ShMirror : public ShVisitor {

private:
	ShEntity *original;
	ShPoint3d center;
	double angle;

public:
	ShMirror(const ShPoint3d& center, double angle);
	~ShMirror();

	virtual void Visit(ShLine *line);
	virtual void Visit(ShCircle *circle);
	virtual void Visit(ShArc *arc);
	virtual void Visit(ShPolyLine *polyLine);


	void SetOriginal(ShEntity *original) { this->original = original; }
};

#endif //_SHMIRROR_H