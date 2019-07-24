
#include "ShDraftSetting.h"

ShDraftSetting ShDraftSetting::instance;


ShDraftSetting::ShDraftSetting() {

}

ShDraftSetting::~ShDraftSetting() {

}


ShDraftSetting* ShDraftSetting::getInstance() {

	return &(ShDraftSetting::instance);
}
