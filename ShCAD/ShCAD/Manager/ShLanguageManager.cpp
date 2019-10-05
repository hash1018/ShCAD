
#include "ShLanguageManager.h"
#include <qfile.h>
#include <qsettings.h>
#include <qdir.h>

ShLanguageManager::ShLanguageManager()
	:type(Interface), settings(nullptr),language(English) {

}

ShLanguageManager::~ShLanguageManager() {

	if (this->settings != nullptr)
		delete this->settings;
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


QString ShLanguageManager::getValue(const Type &type, const QString &key) {

	if (this->type != type) {
		if (this->settings != nullptr) {
			delete this->settings;
			this->settings = nullptr;
		}

		this->type = type;
	}


	if (this->settings == nullptr) {
		QString filePath = QDir::currentPath() + "/Language/" + this->ConvertDirectoryName(this->language) +
			"/" + this->ConvertFileName(type);

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

QString ShLanguageManager::ConvertFileName(const Type &type) {

	if (type == Type::Interface)
		return QString("interface.ini");
	else if (type == Type::Command)
		return QString("command.ini");

	return QString("interface.ini");
}