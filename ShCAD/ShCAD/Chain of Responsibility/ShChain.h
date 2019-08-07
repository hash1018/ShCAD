
#ifndef _SHCHAIN_H
#define _SHCHAIN_H


//Chain of Responsibility pattern.

class ShRequest;

class ShChain {

protected:
	ShChain *chain;

public:
	ShChain(ShChain *chain = nullptr);
	~ShChain();

	virtual void request(ShRequest *request);

};

#endif //_SHCHAIN_H