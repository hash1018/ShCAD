
#ifndef _SHLINESTYLE_H
#define _SHLINESTYLE_H

class ShLineStyle {

public:
	enum Type {
		Normal,
		ByLayer,
		ByBlock,
	};

private:
	unsigned short pattern;
	Type type;

public:
	ShLineStyle();
	ShLineStyle(unsigned short pattern, Type type = Type::Normal);
	ShLineStyle(const ShLineStyle &other);
	~ShLineStyle();

	ShLineStyle& operator=(const ShLineStyle &other);

	bool operator==(const ShLineStyle &other);
	bool operator!=(const ShLineStyle &other);

	void setPattern(unsigned short pattern) { this->pattern = pattern; }
	void setType(Type type) { this->type = type; }

	inline unsigned short getPattern() const { return this->pattern; }
	inline Type getType() const { return this->type; }
};

#endif //_SHLINESTYLE_H