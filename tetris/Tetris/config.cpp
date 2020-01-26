#include "stdafx.h"

MAKE_KEY(BasicBackGroundImagePath);
MAKE_KEY(PlayingBackGroundImagePath);
MAKE_KEY(GameStartButtonImagePath);
MAKE_KEY(GameEndButtonImagePath);

Config::Config() {

}

Config::~Config() {

}

bool Config::loadConfig(const QString& configPath) {
	bool isResult = true;

	QSettings settings(configPath, QSettings::IniFormat);
	basicBackGroundImagePath_ = settings.value(KeyBasicBackGroundImagePath).toString();
	playingBackGroundImagePath_ = settings.value(KeyPlayingBackGroundImagePath).toString();
	gameStartButtonImagePath_ = settings.value(KeyGameStartButtonImagePath).toString();
	gameEndButtonImagePath_ = settings.value(KeyGameEndButtonImagePath).toString();

	return isResult;
}