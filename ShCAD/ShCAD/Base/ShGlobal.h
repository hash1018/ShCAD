
#ifndef _SHGLOBAL_H
#define _SHGLOBAL_H

class ShCADWidget;
class ShTransaction;


//Facade Pattern.


class ShGlobal {

private:
	ShGlobal();
	~ShGlobal();

public:
	static void undo(ShCADWidget *widget);
	static void redo(ShCADWidget *widget);
	static void selectAll(ShCADWidget *widget);
	static void deleteSelectedEntity(ShCADWidget *widget);
	static void pushNewTransaction(ShCADWidget *widget, ShTransaction *transaction);

};



#endif //_SHGLOBAL_H