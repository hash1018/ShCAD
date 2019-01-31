

#ifndef _SHPROPERTYDATA_H
#define _SHPROPERTYDATA_H

class ShColor {

public:
	enum Type {
		Normal=1,
		ByLayer=2,
		ByBlock=3,
	};

private:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Type type;
	
public:
	ShColor();
	ShColor(unsigned char r, unsigned char g, unsigned b, ShColor::Type type = Normal);
	ShColor(const ShColor& other);
	ShColor& operator=(const ShColor& other);
	~ShColor();
	
	bool operator==(const ShColor& other);

	void SetRed(unsigned char red) { this->r = red; }
	void SetGreen(unsigned char green) { this->g = green; }
	void SetBlue(unsigned char blue) { this->b = blue; }
	void SetType(ShColor::Type type) { this->type = type; }

	inline unsigned char GetRed() const { return this->r; }
	inline unsigned char GetGreen() const { return this->g; }
	inline unsigned char GetBlue() const { return this->b; }
	inline ShColor::Type GetType() const { return this->type; }

};

class ShLineStyle {

public:
	enum Type {
		Normal=1,
		ByLayer=2,
		ByBlock=3,
	};

private:
	unsigned short pattern;
	Type type;

public:
	ShLineStyle();
	ShLineStyle(unsigned short pattern, ShLineStyle::Type type = Normal);
	ShLineStyle(const ShLineStyle& other);
	ShLineStyle& operator=(const ShLineStyle& other);
	~ShLineStyle();

	bool operator==(const ShLineStyle& other);

	void SetPattern(unsigned short pattern) { this->pattern = pattern; }
	void SetType(ShLineStyle::Type type) { this->type = type; }

	inline unsigned short GetPattern() const { return this->pattern; }
	inline ShLineStyle::Type GetType() const { return this->type; }
};

class ShPropertyData {

private:
	ShColor color;
	ShLineStyle lineStyle;

public:
	ShPropertyData();
	ShPropertyData(const ShPropertyData& other);
	ShPropertyData& operator=(const ShPropertyData& other);
	~ShPropertyData();

	void SetColor(const ShColor& color) { this->color = color; }
	void SetLineStyle(const ShLineStyle& lineStyle) { this->lineStyle = lineStyle; }

	inline ShColor GetColor() const { return this->color; }
	inline ShLineStyle GetLineStyle() const { return this->lineStyle; }

};




#endif //_SHPROPERTYDATA_H