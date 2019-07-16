
#ifndef _SHLANGUAGEMANAGER_H
#define _SHLANGUAGEMANAGER_H

#include <qstring.h>
class QSettings;

#define shGetLanValue ShLanguageManager::getInstance()->getValue
#define shGetLanValue_ui(key) (ShLanguageManager::getInstance()->getValue(ShLanguageManager::Interface, key))
#define shGetLanValue_command(key)(ShLanguageManager::getInstance()->getValue(ShLanguageManager::Command,key))

class ShLanguageManager {

public:
	enum Language {
		English,
		Korean,
	};

	enum KeyTable {
		Interface,
		Command,
	};

private:
	Language language;
	QSettings *settings;
	KeyTable keyTable;

private:
	ShLanguageManager();
	~ShLanguageManager();
	static ShLanguageManager instance;

public:
	static ShLanguageManager* getInstance();

	bool setLanguage(Language language);
	QString getValue(const KeyTable &keyTable, const QString &key);
	

private:
	static QString ConvertDirectoryName(const Language &language);
	static QString ConvertFileName(const KeyTable &table);
};

#endif //_SHLANGUAGEMANAGER_H