

#ifndef _SHDIMSTYLEMANAGER_H
#define _SHDIMSTYLEMANAGER_H

class ShDimStyleManager {

private:
	double arrowSize;
	double intervalFromBase;
	double textHeight;

private:
	ShDimStyleManager();
	~ShDimStyleManager();

	static ShDimStyleManager instance;

public:
	static ShDimStyleManager* getInstance();

public:
	void setArrowSize(double arrowSize);
	void setIntervalFromBase(double intervalFromBase);
	void setTextHeight(double textHeight);

	inline double getArrowSize() const { return this->arrowSize; }
	inline double getIntervalFromBase() const { return this->intervalFromBase; }
	inline double getTextHeight() const { return this->textHeight; }

private:
	void updateWidget();
};

#endif //_SHDIMSTYLEMANAGER_H