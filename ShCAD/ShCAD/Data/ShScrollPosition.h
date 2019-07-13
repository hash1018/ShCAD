
#ifndef _SHSCROLLPOSITION_H
#define _SHSCROLLPOSITION_H

class ShScrollPosition {

public:
	double vertical;
	double horizontal;

	ShScrollPosition();
	ShScrollPosition(const double &vertical, const double &horizontal);
	ShScrollPosition(const ShScrollPosition &other);
	~ShScrollPosition();

	ShScrollPosition& operator=(const ShScrollPosition &other);

};

#endif //SHSCROLLPOSITION_H