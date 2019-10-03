
#ifndef _SHPOINTSTYLE_H
#define _SHPOINTSTYLE_H

class ShPointStyle {

public:

	enum PointShape {
		Dot,
		Cross,
		X,
		DotCircle,
		Circle,
		CrossCircle,
		XCircle,
		DotRectangle,
		Rectangle,
		CrossRectangle,
		XRectangle,
		DotCircleRectangle,
		CircleRectangle,
		CrossCircleRectangle,
		XCircleRectangle,
	};

	enum SizeType {
		RelativeToScreen,
		AbsoluteUnits,
	};

private:
	PointShape shape;
	double pointSize;
	SizeType sizeType;

public:
	ShPointStyle();
	~ShPointStyle();

public:
	void setShape(PointShape shape) { this->shape = shape; }
	void setPointSize(double pointSize) { this->pointSize = pointSize; }
	void setSizeType(SizeType sizeType) { this->sizeType = sizeType; }

public:
	inline PointShape getShape() const { return this->shape; }
	inline double getPointSize() const { return this->pointSize; }
	inline SizeType getSizeType() const { return this->sizeType; }

};


#endif //_SHPOINTSTYLE_H