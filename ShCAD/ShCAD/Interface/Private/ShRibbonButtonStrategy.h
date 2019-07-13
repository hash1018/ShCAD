

#ifndef _SHRIBBONBUTTONSTRATEGY_H
#define _SHRIBBONBUTTONSTRATEGY_H

#include "Interface\Item\ShIcon.h"

class ShRibbonButtonStrategy {

public:
	ShRibbonButtonStrategy();
	virtual ~ShRibbonButtonStrategy() = 0;

	virtual void execute() = 0;
	virtual ShIcon getIcon() = 0;
	virtual QString getToolTip() = 0;

};

class ShRibbonCircleButtonCenterRadiusStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonCircleButtonCenterRadiusStrategy();
	~ShRibbonCircleButtonCenterRadiusStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();

};

class ShRibbonCircleButtonCenterDiameterStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonCircleButtonCenterDiameterStrategy();
	~ShRibbonCircleButtonCenterDiameterStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();

};

class ShRibbonCircleButtonTwoPointStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonCircleButtonTwoPointStrategy();
	~ShRibbonCircleButtonTwoPointStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonCircleButtonThreePointStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonCircleButtonThreePointStrategy();
	~ShRibbonCircleButtonThreePointStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

////////////////////////////////////////////////////////////////////////

class ShRibbonArcButtonThreePointStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonThreePointStrategy();
	~ShRibbonArcButtonThreePointStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonStartCenterEndStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonStartCenterEndStrategy();
	~ShRibbonArcButtonStartCenterEndStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonStartCenterAngleStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonStartCenterAngleStrategy();
	~ShRibbonArcButtonStartCenterAngleStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonStartCenterLengthStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonStartCenterLengthStrategy();
	~ShRibbonArcButtonStartCenterLengthStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonStartEndAngleStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonStartEndAngleStrategy();
	~ShRibbonArcButtonStartEndAngleStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonStartEndDirectionStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonStartEndDirectionStrategy();
	~ShRibbonArcButtonStartEndDirectionStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonStartEndRadiusStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonStartEndRadiusStrategy();
	~ShRibbonArcButtonStartEndRadiusStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonCenterStartEndStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonCenterStartEndStrategy();
	~ShRibbonArcButtonCenterStartEndStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonCenterStartAngleStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonCenterStartAngleStrategy();
	~ShRibbonArcButtonCenterStartAngleStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonArcButtonCenterStartLengthStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonArcButtonCenterStartLengthStrategy();
	~ShRibbonArcButtonCenterStartLengthStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};


class ShRibbonRectangleButtonStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonRectangleButtonStrategy();
	~ShRibbonRectangleButtonStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonPolygonButtonStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonPolygonButtonStrategy();
	~ShRibbonPolygonButtonStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

class ShRibbonPolyLineButtonStrategy : public ShRibbonButtonStrategy {

public:
	ShRibbonPolyLineButtonStrategy();
	~ShRibbonPolyLineButtonStrategy();

	virtual void execute();
	virtual ShIcon getIcon();
	virtual QString getToolTip();
	static ShIcon getIcon_();
};

#endif //_RIBBONBUTTONSTRATEGY_H
