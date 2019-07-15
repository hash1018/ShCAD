
#ifndef _SHGLOBAL_H
#define _SHGLOBAL_H

class ShCADWidget;


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

};



#endif //_SHGLOBAL_H