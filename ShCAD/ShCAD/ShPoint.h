



#ifndef _SHPOINT_H
#define _SHPOINT_H


/* Represents a 3d coordinates (x / y / z) */

class ShPoint3d {

public:
	double x;
	double y;
	double z;

public:
	ShPoint3d();
	ShPoint3d(double x, double y, double z = 0);
	ShPoint3d(const ShPoint3d& other);
	ShPoint3d& operator=(const ShPoint3d& other);
	~ShPoint3d();

	bool operator==(const ShPoint3d &other);

};

#endif //_SHPOINT_H