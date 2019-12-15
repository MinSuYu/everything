#include "stdafx.h"

MAKE_KEY(BasicBackGroundImagePath);
MAKE_KEY(PlayingBackGroundImagePath);

Config::Config() {

}

Config::~Config() {

}

bool Config::loadConfig(const QString& configPath) {
	bool isResult = true;

	QSettings settings(configPath, QSettings::IniFormat);
	basicBackGroundImagePath_ = settings.value(KeyBasicBackGroundImagePath).toString();
	playingBackGroundImagePath_ = settings.value(KeyPlayingBackGroundImagePath).toString();

	return isResult;
}