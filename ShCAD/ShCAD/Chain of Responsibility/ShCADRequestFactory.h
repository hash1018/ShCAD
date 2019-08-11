
#ifndef _SHCADREQUESTFACTORY_H
#define _SHCADREQUESTFACTORY_H

class ShCAD;
class ShCADRequestStrategy;
class ShRequest;

class ShCADRequestFactory {

public:
	ShCADRequestFactory();
	~ShCADRequestFactory();

	static ShCADRequestStrategy* create(ShCAD *shCAD, ShRequest *request);
};

#endif //_SHCADREQUESTFACTORY_H