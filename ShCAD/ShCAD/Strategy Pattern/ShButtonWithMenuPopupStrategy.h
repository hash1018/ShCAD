

#ifndef _SHBUTTONWITHMENUPOPUPSTRATEGY_H
#define _SHBUTTONWITHMENUPOPUPSTRATEGY_H
#include <qicon.h>
class QString;
class ShButtonWithMenuPopupStrategy {

public:
	ShButtonWithMenuPopupStrategy();
	virtual ~ShButtonWithMenuPopupStrategy() = 0;

	virtual void Do() = 0;
	virtual QIcon GetIcon()= 0;
	virtual QString GetToolTip() = 0;

protected:
	QIcon GetIcon(const QString& filePath);
	static QIcon GetIcon_(const QString& filePath);
};


class ShCircleButtonCenterRadiusStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShCircleButtonCenterRadiusStrategy();
	~ShCircleButtonCenterRadiusStrategy();

	virtual void Do();
	virtual QIcon GetIcon();
	
	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShCircleButtonCenterDiameterStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShCircleButtonCenterDiameterStrategy();
	~ShCircleButtonCenterDiameterStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
	
};

class ShCircleButtonTwoPointStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShCircleButtonTwoPointStrategy();
	~ShCircleButtonTwoPointStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShCircleButtonThreePointStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShCircleButtonThreePointStrategy();
	~ShCircleButtonThreePointStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

////////////////////////////////////////////////////////////////////////

class ShArcButtonThreePointStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonThreePointStrategy();
	~ShArcButtonThreePointStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonStartCenterEndStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonStartCenterEndStrategy();
	~ShArcButtonStartCenterEndStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonStartCenterAngleStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonStartCenterAngleStrategy();
	~ShArcButtonStartCenterAngleStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonStartCenterLengthStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonStartCenterLengthStrategy();
	~ShArcButtonStartCenterLengthStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonStartEndAngleStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonStartEndAngleStrategy();
	~ShArcButtonStartEndAngleStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonStartEndDirectionStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonStartEndDirectionStrategy();
	~ShArcButtonStartEndDirectionStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonStartEndRadiusStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonStartEndRadiusStrategy();
	~ShArcButtonStartEndRadiusStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonCenterStartEndStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonCenterStartEndStrategy();
	~ShArcButtonCenterStartEndStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonCenterStartAngleStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonCenterStartAngleStrategy();
	~ShArcButtonCenterStartAngleStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};

class ShArcButtonCenterStartLengthStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShArcButtonCenterStartLengthStrategy();
	~ShArcButtonCenterStartLengthStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();
};


class ShRectangleButtonStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShRectangleButtonStrategy();
	~ShRectangleButtonStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();

};

class ShPolygonButtonStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShPolygonButtonStrategy();
	~ShPolygonButtonStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();

};

class ShPolyLineButtonStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShPolyLineButtonStrategy();
	~ShPolyLineButtonStrategy();

	virtual void Do();
	virtual QIcon GetIcon();

	static QIcon GetIcon_();

	virtual QString GetToolTip();

};





#endif //_SHBUTTONWITHMENUPOPUPSTRATEGY_H