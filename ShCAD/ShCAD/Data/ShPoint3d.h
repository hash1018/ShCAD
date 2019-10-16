
#ifndef _SHPOINT3D_H
#define _SHPOINT3D_H

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
	bool isEqual(const ShPoint3d &other, double epsilon = 0.0001);

	void move(double dx, double dy, double dz = 0.0);


};

#endif //_SHPOINT3D_H