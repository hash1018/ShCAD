

#ifndef _SHTRANSACTION_H
#define _SHTRANSACTION_H

#include <qstring.h>

class ShTransaction {
	friend class ShTransactionStack;

protected:
	QString transactionName;

public:
	ShTransaction();
	ShTransaction(const QString &transactionName);
	virtual void redo() = 0;
	virtual void undo() = 0;

	inline QString getTransactionName() const { return this->transactionName; }

private:
	void destroy();
protected:
	virtual ~ShTransaction() = 0;
};

#endif //_SHTRANSACTION_H