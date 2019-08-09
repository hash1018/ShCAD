
#include "ShDraftData.h"
#include "Base\ShDraftSetting.h"

ShDraftData::ShDraftData()
	:orthModeOn(false), disposableSnap(ObjectSnap::ObjectSnapNothing), objectSnapData(nullptr) {

	ShDraftSetting *setting = ShDraftSetting::getInstance();

	setting->getObjectSnapData();

}

ShDraftData::~ShDraftData() {

}

void ShDraftData::setOrthMode(bool on) {

	this->orthModeOn = on;
}

void ShDraftData::setDisposableSnap(ObjectSnap objectSnap) {

	this->disposableSnap = objectSnap;
}
