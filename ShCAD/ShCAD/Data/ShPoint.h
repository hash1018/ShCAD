
#ifndef _SHPOINT_H
#define _SHPOINT_H

class ShPoint3d {

public:
	double x;
	double y;
	double z;

public:
	ShPoint3d();
	ShPoint3d(double x, double y, double z = 0);
	ShPoint3d(const ShPoint3d &other);
	~ShPoint3d();
	ShPoint3d& operator=(const ShPoint3d &other);

	bool operator==(const ShPoint3d &other);


};

#endif //_SHPOINT_H