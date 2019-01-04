



#ifndef _SHVECTOR_H
#define _SHVECTOR_H


/* Represents a 3d coordinates (x / y / z) */

class ShVector {

public:
	double x;
	double y;
	double z;

public:
	ShVector();
	ShVector(double x, double y, double z = 0);
	ShVector(const ShVector& other);
	ShVector& operator=(const ShVector& other);
	~ShVector();

	bool operator==(const ShVector &other);

};

#endif //_SHVECTOR_H