
#ifndef _SHCOLOR_H
#define _SHCOLOR_H

class ShColor {

public:
	enum Type {
		Invalid,
		Normal,
		ByBlock,
		ByLayer,
	};

private:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Type type;

public:
	ShColor();
	ShColor(unsigned char r, unsigned char g, unsigned char b, ShColor::Type type = Normal);
	ShColor(const ShColor &other);
	~ShColor();

	ShColor& operator=(const ShColor &other);
	bool operator==(const ShColor &other);
	bool operator!=(const ShColor &other);

	void setRed(unsigned char red) { this->r = red; }
	void setGreen(unsigned char green) { this->g = green; }
	void setBlue(unsigned char blue) { this->b = blue; }
	void setType(Type type) { this->type = type; }

	inline unsigned char getRed() const { return this->r; }
	inline unsigned char getGreen() const { return this->g; }
	inline unsigned char getBlue() const { return this->b; }
	inline ShColor::Type getType() const { return this->type; }

};

#endif //_SHCOLOR_H