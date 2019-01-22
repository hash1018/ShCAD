

#ifndef _SHPROPERTYDATA_H
#define _SHPROPERTYDATA_H

class ShColor {

public:
	enum Type {
		Normal=1,
		ByLayer=2,
		ByBlock=3,
	};

public:
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


};

class ShPropertyData {

public:
	ShColor color;

public:
	ShPropertyData();
	ShPropertyData(const ShPropertyData& other);
	ShPropertyData& operator=(const ShPropertyData& other);
	~ShPropertyData();


};




#endif //_SHPROPERTYDATA_H