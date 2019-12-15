#include "stdafx.h"

Config::Config() {

}

Config::~Config() {

}

bool Config::loadConfig(const QString& configPath) {
	bool isResult = true;

	QSettings settings(configPath, QSettings::IniFormat);
	settings.setValue("BasicBackGroundImagePath", basicBackGroundImagePath_);
	settings.setValue("PlayingBackGroundImagePath", playingBackGroundImagePath_);

	return isResult;
}