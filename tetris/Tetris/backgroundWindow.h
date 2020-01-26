#pragma once

class BackgroundWindow : public QWidget {
	Q_OBJECT
public:
	BackgroundWindow(QWidget *parent);
	~BackgroundWindow();

public:
	void load(const QSize& size, const QString& basicPath, const QString& playingPath, const QString& gameStartPath, const QString& gameEndPath);
	void setIsPlaying(const bool isPlaying);

private:
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

private:
	QTimer *timer_ = nullptr;

	QImage basicImage_;
	QImage playingImage_;
	QImage gameStartImage_;
	QImage gameEndImage_;
	QSize windowsSize_;

	bool isPlaying_ = false;
};