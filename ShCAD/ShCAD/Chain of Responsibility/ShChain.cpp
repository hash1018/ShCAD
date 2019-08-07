
#include "ShChain.h"

ShChain::ShChain(ShChain *chain)
	:chain(chain) {

}

ShChain::~ShChain() {

}

void ShChain::request(ShRequest *request) {

	if (this->chain != nullptr)
		this->chain->request(request);
}