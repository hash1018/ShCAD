

#ifndef _SHBUTTONWITHMENUPOPUPSTRATEGY_H
#define _SHBUTTONWITHMENUPOPUPSTRATEGY_H
#include <qlist.h>
#include <qicon.h>
class ShButtonWithMenuPopupStrategy;
class QAction;
class ShButtonWithMenuPopupStrategyList {

protected:
	QList<ShButtonWithMenuPopupStrategy*> list;
	int currentIndex;

public:
	ShButtonWithMenuPopupStrategyList();
	virtual ~ShButtonWithMenuPopupStrategyList() = 0;

	void Clear();
	void Add(ShButtonWithMenuPopupStrategy* strategy);
	inline int GetLength() const { return this->list.length(); }
	inline int GetCurrentIndex() const { return this->currentIndex; }
	inline ShButtonWithMenuPopupStrategy* At(int index) const { return this->list.at(index); }
};


class ShCircleButtonStrategyList : public ShButtonWithMenuPopupStrategyList{

public:
	ShCircleButtonStrategyList();
	~ShCircleButtonStrategyList();
};


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class ShButtonWithMenuPopupStrategy {

public:
	ShButtonWithMenuPopupStrategy();
	virtual ~ShButtonWithMenuPopupStrategy() = 0;

	virtual void Do() = 0;
	virtual QIcon GetIcon() const = 0;
	virtual QAction* GetAction() = 0;
};


class ShCircleButtonCenterRadiusStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShCircleButtonCenterRadiusStrategy();
	~ShCircleButtonCenterRadiusStrategy();

	virtual void Do();
	virtual QIcon GetIcon() const;
	virtual QAction* GetAction();

};

class ShCircleButtonCenterDiameterStrategy : public ShButtonWithMenuPopupStrategy {

public:
	ShCircleButtonCenterDiameterStrategy();
	~ShCircleButtonCenterDiameterStrategy();

	virtual void Do();
	virtual QIcon GetIcon() const;
	virtual QAction* GetAction();
};


#endif //_SHBUTTONWITHMENUPOPUPSTRATEGY_H