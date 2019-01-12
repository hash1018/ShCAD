

#ifndef _SHPREVIEW_H
#define _SHPREVIEW_H

#include "ShComposite.h"

class ShPreview : public ShComposite {

public:
	ShPreview();
	~ShPreview();
	ShPreview(const ShPreview& other);
	ShPreview& operator=(const ShPreview& other);

	ShPreview* Clone();
	void Accept(ShVisitor *shVisitor);

	
	void Empty();
	void DeleteAll();
};

#endif //_SHPREVIEW_H