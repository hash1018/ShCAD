
#include "ShTransaction.h"

ShTransaction::ShTransaction()
	:transactionName("") {

}

ShTransaction::ShTransaction(const QString &transactionName)
	: transactionName(transactionName) {

}

ShTransaction::~ShTransaction() {

}

void ShTransaction::destroy() {
	
	delete this;
}