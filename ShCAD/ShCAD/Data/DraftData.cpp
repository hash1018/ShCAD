
#include "DraftData.h"
#include "Base\ShDraftSetting.h"

DraftData::DraftData()
	:orthModeOn(false), disposableSnap(ObjectSnap::ObjectSnapNothing), objectSnapData(nullptr) {

	ShDraftSetting *setting = ShDraftSetting::getInstance();

	setting->getObjectSnapData();

}

DraftData::~DraftData() {

}

void DraftData::setOrthMode(bool on) {

	this->orthModeOn = on;
}

void DraftData::setDisposableSnap(ObjectSnap objectSnap) {

	this->disposableSnap = objectSnap;
}
