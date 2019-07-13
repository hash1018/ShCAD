
#include "ShLanguageManager.h"
#include <qfile.h>
#include <qsettings.h>
#include <qdir.h>
ShLanguageManager ShLanguageManager::instance;

ShLanguageManager::ShLanguageManager()
	:keyTable(Interface), settings(nullptr),language(English) {


}

ShLanguageManager::~ShLanguageManager() {

	if (this->settings != nullptr)
		delete this->settings;
}

ShLanguageManager* ShLanguageManager::getInstance() {

	return &(ShLanguageManager::instance);
}

bool ShLanguageManager::setLanguage(Language language) {

	QString filePath = QDir::currentPath() + "/Language/" + ShLanguageManager::ConvertDirectoryName(language);

	if (!QFile(filePath).exists()) {
		Q_ASSERT_X(false, "ShLanguageManager::setLanguage", "following language donsn't support.");
		return false;
	}
	
	this->language = language;

	if (this->settings != nullptr) {
		delete this->settings;
		this->settings = nullptr;
	}

	return true;
}


QString ShLanguageManager::getValue(const KeyTable &keyTable,const QString &key) {

	if (this->keyTable != keyTable) {
		if (this->settings != nullptr) {
			delete this->settings;
			this->settings = nullptr;
		}

		this->keyTable = keyTable;
	}


	if (this->settings == nullptr) {
		QString filePath = QDir::currentPath() + "/Language/" + this->ConvertDirectoryName(this->language) +
			"/" + this->ConvertFileName(keyTable);

		if (!QFile(filePath).exists())
			Q_ASSERT_X(false, "ShLanguageManager::ShLanguageManager", "invalid filePath");

		this->settings = new QSettings(filePath, QSettings::IniFormat);
		this->settings->setIniCodec("UTF-8");

	}

	return this->settings->value(key).toString();
}

QString ShLanguageManager::ConvertDirectoryName(const Language &language) {

	if (language == Language::English)
		return QString("English");
	else if (language == Language::Korean)
		return QString("Korean");

	return QString("English");
}

QString ShLanguageManager::ConvertFileName(const KeyTable &table) {

	if (table == KeyTable::Interface)
		return QString("interface.ini");

	return QString("interface.ini");
}