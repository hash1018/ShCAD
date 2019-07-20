
#ifndef _SHKEYHANDLER_H
#define _SHKEYHANDLER_H

#include <qlist.h>

class ShCADWidget;
class ShActionHandler;
class QKeyEvent;
class ShKey;
template <class T> class ShCustomKey;

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
		ShKeyHandler::ShBuilder& allowEnter();
		ShKeyHandler::ShBuilder& allowEsc();
		ShKeyHandler::ShBuilder& allowInput();
		ShKeyHandler::ShBuilder& allowCustom(ShKey *key);
		
		ShKeyHandler* build();
	};

public:
	ShKeyHandler(const ShKeyHandler::ShBuilder &builder);
	~ShKeyHandler();

	void keyPressEvent(QKeyEvent *event);
	

};
#endif //SHKEYHANDLER_H