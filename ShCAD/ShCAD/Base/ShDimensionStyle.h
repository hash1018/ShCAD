

#ifndef _SHDIMENSIONSTYLE_H
#define _SHDIMENSIONSTYLE_H

#include <qstring.h>

class ShLine;
class ShLayer;
class ShPoint3d;
class ShPropertyData;

class ShDimensionExtensionLineStyle {

private:
	double offsetFromOrigin;
	double extendBeyondDimensionLine;
	bool suppressExtensionLine;
	bool suppressExtensionLine2;

public:
	ShDimensionExtensionLineStyle();
	ShDimensionExtensionLineStyle(double offsetFromOrigin, double extendBeyondDimensionLine, bool suppressExtensionLine, bool suppressExtensionLine2);
	ShDimensionExtensionLineStyle(const ShDimensionExtensionLineStyle &other);
	~ShDimensionExtensionLineStyle();
	ShDimensionExtensionLineStyle& operator=(const ShDimensionExtensionLineStyle &other);

public:
	void setOffsetFromOrigin(double offsetFromOrigin) { this->offsetFromOrigin = offsetFromOrigin; }
	void setExtendBeyondDimensionLine(double extendBeyondDimensionLine) { this->extendBeyondDimensionLine = extendBeyondDimensionLine; }
	void setSuppressExtensionLine(bool suppressExtensionLine) { this->suppressExtensionLine = suppressExtensionLine; }
	void setSupressExtensionLine2(bool supressExtensionLine2) { this->suppressExtensionLine2 = suppressExtensionLine2; }

public:
	inline double getOffsetFromOrigin() const { return this->offsetFromOrigin; }
	inline double getExtendBeyondDimensionLine() const { return this->extendBeyondDimensionLine; }
	inline bool getSupressExtensionLine() const { return this->suppressExtensionLine; }
	inline bool getSupressExtensionLine2() const { return this->suppressExtensionLine2; }

public:
	ShLine* createExtensionLine(const ShPoint3d &origin, const ShPoint3d &dim, const ShPropertyData &propertyData, ShLayer *layer);
	ShLine* createExtensionLine2(const ShPoint3d &origin, const ShPoint3d &dim, const ShPropertyData &propertyData, ShLayer *layer);
};

////////////////////////////////////////////////

class ShDimensionLineStyle {

private:

public:
	ShDimensionLineStyle();
	~ShDimensionLineStyle();
};

/////////////////////////////////////////////////

class ShDimensionArrowStyle {

public:
	enum Arrowheads {
		ClosedFilled,
		ClosedBlank,
	};

private:
	Arrowheads first;
	Arrowheads second;
	double arrowSize;

public:
	ShDimensionArrowStyle();
	ShDimensionArrowStyle(Arrowheads first, Arrowheads second, double arrowSize);
	ShDimensionArrowStyle(const ShDimensionArrowStyle &other);
	~ShDimensionArrowStyle();

	ShDimensionArrowStyle& operator=(const ShDimensionArrowStyle &other);

public:
	void setFirstArrowheads(Arrowheads first) { this->first = first; }
	void setSecondArrowheads(Arrowheads second) { this->second = second; }
	void setArrowSize(double arrowSize) { this->arrowSize = arrowSize; }

public:
	inline Arrowheads getFirstArrowheads() const { return this->first; }
	inline Arrowheads getSecondArrowheads() const { return this->second; }
	inline double getArrowSize() const { return this->arrowSize; }
};

///////////////////////////////////////////////////

class ShDimensionTextStyle {

private:
	double textHeight;

public:
	ShDimensionTextStyle();
	ShDimensionTextStyle(double textHeight);
	ShDimensionTextStyle(const ShDimensionTextStyle &other);
	~ShDimensionTextStyle();

	ShDimensionTextStyle& operator=(const ShDimensionTextStyle &other);

public:
	void setTextHeight(double textHeight) { this->textHeight = textHeight; }

public:
	inline double getTextHeight() const { return this->textHeight; }
};

////////////////////////////////////////////////////

class ShDimensionStyle {

private:
	QString name;
	ShDimensionExtensionLineStyle dimensionExtensionLineStyle;
	ShDimensionArrowStyle dimensionArrowStyle;
	ShDimensionTextStyle dimensionTextStyle;

public:
	ShDimensionStyle(const QString &name);
	~ShDimensionStyle();

public:
	void setDimensionExtensionLineStyle(const ShDimensionExtensionLineStyle &dimensionExtensionLineStyle) { this->dimensionExtensionLineStyle = dimensionExtensionLineStyle; }
	void setDiemnsionArrowStyle(const ShDimensionArrowStyle &dimensionArrowStyle) { this->dimensionArrowStyle = dimensionArrowStyle; }
	void setDimensionTextStyle(const ShDimensionTextStyle &dimensionTextStyle) { this->dimensionTextStyle = dimensionTextStyle; }
	void setName(const QString &name) { this->name = name; }

public:
	inline const ShDimensionExtensionLineStyle& getDimensionExtensionLineStyle() const { return this->dimensionExtensionLineStyle; }
	inline const ShDimensionArrowStyle& getDimensionArrowStyle() const { return this->dimensionArrowStyle; }
	inline const ShDimensionTextStyle& getDimensionTextStyle() const { return this->dimensionTextStyle; }
	inline const QString& getName() const { return this->name; }
};

//////////////////////////////////////////////////////

#endif //_SHDIMENSIONSTYLE_H