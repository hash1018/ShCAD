

#ifndef _SHDRAWPREVIEWCOMMAND_H
#define _SHDRAWPREVIEWCOMMAND_H

#include "ShCommand.h"
#include "ShVector.h"

class ShRubberBand;
class ShGraphicView;
class ShDrawPreviewCommand : public ShCommand {

private:
	ShGraphicView *view;
	bool isDrawingRubberBand;
	ShVector start;
	ShVector end;

public:
	//  **if you call this constructor, rubberband would be drawn
	//  **or you can add some by calling set function
	ShDrawPreviewCommand(ShGraphicView *view, const ShVector& start, const ShVector& end);

	//  **if you call this constructor, there is no to be drawn
	//** or you can add some by calling set function
	ShDrawPreviewCommand(ShGraphicView *view);

	
	~ShDrawPreviewCommand();

	virtual void Execute();

	void SetDrawingRubberBand(bool enabled);
	void SetStart(const ShVector& rubberBandStart);
	void SetEnd(const ShVector& rubberBandEnd);
};

#endif //_SHDRAWPREVIEWCOMMAND_H