
#ifndef _SHPREVIEW_H
#define _SHPREVIEW_H

#include "ShComposite.h"

class ShPreview : public ShComposite {

public:
	ShPreview();
	ShPreview(const ShPreview &other);
	~ShPreview();
	ShPreview& operator=(const ShPreview &other);

	ShPreview* clone();
	void accept(ShVisitor *visitor);

	void empty();
	void clear();

};

#endif //_SHPREVIEW_H