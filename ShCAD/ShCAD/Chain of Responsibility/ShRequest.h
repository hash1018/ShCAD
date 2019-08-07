
#ifndef _SHREQUEST_H
#define _SHREQUEST_H

class ShRequest {

public:
	enum RequestType {
		RequestCreateNewCADWidget,

	};

protected:
	RequestType type;

public:
	ShRequest(RequestType type);
	virtual ~ShRequest() = 0;

	inline RequestType getType() const { return this->type; }

};

class ShCreateNewCADWidgetRequest : public ShRequest {

public:
	ShCreateNewCADWidgetRequest();
	~ShCreateNewCADWidgetRequest();

};

#endif //_SHREQUEST_H