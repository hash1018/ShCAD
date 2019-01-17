

#include "ShDirectoryManager.h"
#include <qdir.h>
ShDirectoryManager::ShDirectoryManager() {

}

ShDirectoryManager::~ShDirectoryManager() {

}

QString ShDirectoryManager::GetCurrentPath() {

	return QDir::currentPath();
}

QString ShDirectoryManager::GetImageUiPath() {

	QString path = QDir::currentPath() + "\\res\\ui";

	return path;

}