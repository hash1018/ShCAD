
#ifndef _SHLANGUAGEMANAGER_H
#define _SHLANGUAGEMANAGER_H

#include "Base\ShSingleton.h"
#include <qstring.h>
class QSettings;

#define shGetLanValue ShLanguageManager::getInstance()->getValue
#define shGetLanValue_ui(key) (ShLanguageManager::getInstance()->getValue(ShLanguageManager::Interface, key))
#define shGetLanValue_command(key)(ShLanguageManager::getInstance()->getValue(ShLanguageManager::Command,key))

class ShLanguageManager {

	DeclareSingleton(ShLanguageManager)

public:
	enum Language {
		English,
		Korean,
	};

	enum Type {
		Interface,
		Command,
	};

private:
	Language language;
	QSettings *settings;
	Type type;

public:
	bool setLanguage(Language language);
	QString getValue(const Type &type, const QString &key);
	

private:
	static QString ConvertDirectoryName(const Language &language);
	static QString ConvertFileName(const Type &type);
};

#endif //_SHLANGUAGEMANAGER_H