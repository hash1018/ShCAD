
#ifndef _SHKEYHANDLER_H
#define _SHKEYHANDLER_H

#include <qlist.h>
#include "ShKeyType.h"

class ShCADWidget;
class ShActionHandler;
class QKeyEvent;
class ShKey;
class ShAbstractCustomKey;

//Builder Pattern.

class ShKeyHandler {

private:
	ShCADWidget *widget;
	ShActionHandler *actionHandler;
	bool allowedInput;
	QList<ShKey*> list;

public:
	class ShBuilder {
		friend class ShKeyHandler;
	private:
		ShCADWidget *widget;
		ShActionHandler *actionHandler;
		bool allowedInput;
		QList<ShKey*> list;

	public:
		ShBuilder(ShCADWidget *widget, ShActionHandler *actionHandler);
		~ShBuilder();
		ShKeyHandler::ShBuilder& allowKey(KeyType keyType);
		ShKeyHandler::ShBuilder& allowInput();
		ShKeyHandler::ShBuilder& allowCustom(ShAbstractCustomKey *key);
		
		ShKeyHandler* build();
	};

public:
	ShKeyHandler(const ShKeyHandler::ShBuilder &builder);
	~ShKeyHandler();

	void keyPressEvent(QKeyEvent *event);
	

};
#endif //SHKEYHANDLER_H