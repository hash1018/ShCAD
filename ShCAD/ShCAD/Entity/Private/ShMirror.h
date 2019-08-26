
#ifndef _SHMIRROR_H
#define _SHMIRROR_H

#include "ShVisitor.h"
#include "Data\ShPoint.h"

class ShEntity;

class ShMirror : public ShVisitor {

private:
	ShEntity *original;
	ShPoint3d center;
	double angle;

public:
	ShMirror(const ShPoint3d &center, double angle);
	~ShMirror();

	virtual void visit(ShLine *line);
	virtual void visit(ShCircle *circle);

public:
	void setOriginal(ShEntity *original) { this->original = original; }

};

#endif //_SHMIRROR_H