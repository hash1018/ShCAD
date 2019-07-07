
#ifndef _SHICON_H
#define _SHICON_H

#include <qicon.h>

class ShIcon : public QIcon {

public:
	ShIcon(const QString &filePath, const QColor &maskFromColor = QColor(255, 255, 255));
	~ShIcon();

	ShIcon& operator=(const ShIcon &icon);
};

#endif //_SHICON_H