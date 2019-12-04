#pragma once

class Config {
public:
	Config();
	Config(const QString& configPath);
	~Config();

public:
	const QString& basicBackGroundImagePath() const {return basicBackGroundImagePath_; }
	const QString& playingBackGroundImagePath() const { return playingBackGroundImagePath_; }
	const QString& gameStartButtonImagePath() const { return gameStartButtonImagePath_; }
	const QString& gameEndButtonImagePath() const { return gameEndButtonImagePath_; }
	const QString& basicBackGroundSoundPath() const { return basicBackGroundSoundPath_; }
	const QString& deleteLineEffectSoundPath() const { return deleteLineEffectSoundPath_; }
	const QString& moveEffectSoundPath() const { return moveEffectSoundPath_; }
	const QString& spaceButtonEffectSoundPath() const { return spaceButtonEffectSoundPath_; }

public:
	bool loadConfig(const QString& configPath);

private:
	QString basicBackGroundImagePath_;
	QString playingBackGroundImagePath_;
	QString gameStartButtonImagePath_;
	QString gameEndButtonImagePath_;

	QString basicBackGroundSoundPath_;
	QString deleteLineEffectSoundPath_;
	QString moveEffectSoundPath_;
	QString spaceButtonEffectSoundPath_;
};

typedef Singleton<Config> ConfigSigleton;

#define ConfigInstance() ConfigSigleton::instance()