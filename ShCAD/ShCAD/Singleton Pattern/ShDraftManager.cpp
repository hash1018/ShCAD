

#include "ShDraftManager.h"

ShDraftManager ShDraftManager::instance;

ShDraftManager::ShDraftManager() {

}

ShDraftManager::~ShDraftManager() {

}

ShDraftManager* ShDraftManager::GetInstance() {

	return &instance;
}