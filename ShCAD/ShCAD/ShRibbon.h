


#ifndef _SHRIBBON_H
#define _SHRIBBON_H

#include <qtoolbar.h>
class QTabWidget;
class ShWidgetInTab;
class ShColumnWidget;
class ShRibbon : public QToolBar {

protected:
	QTabWidget *tab;

public:
	ShRibbon(QWidget *parent = 0);
	ShRibbon(const QSize& size, QWidget *parent = 0);
	ShRibbon(int height, QWidget *parent = 0);
	~ShRibbon();

	ShWidgetInTab* AddTab(const QString &title);
};


class ShWidgetInTab : public QToolBar {
	friend class ShRibbon;

private:
	ShWidgetInTab(QWidget *parent);
	~ShWidgetInTab();

public:
	ShColumnWidget* AddColumn();
	ShColumnWidget* AddColumn(const QString& columnTitle);

	ShColumnWidget *AddColumn(const QString& columnTitle, int columnWidth);
	

};

class ShColumnWidget : public QWidget {
	friend class ShWidgetInTab;

public:
	enum ColumnTitleArea {
		TopColumnTitleArea = 0, 
		BottomColumnTitleArea = 1
	};

private:
	QString title;
	ColumnTitleArea area;
	//child item such as pushButton,listBox.. etc must be within range of following rect.
	QRect layoutRect;
	int index;
private:
	ShColumnWidget(QWidget *parent, const QString& title);
	~ShColumnWidget();
	

public:
	void SetColumnTitleArea(ColumnTitleArea area);
	void AddItem(QWidget *widget, const QRect& rect);

protected:
	void paintEvent(QPaintEvent* event);

};
#endif //_SHRIBBON_H