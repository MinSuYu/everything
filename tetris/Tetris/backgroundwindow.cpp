#include "stdafx.h"
#include "backgroundwindow.h"

BackgroundWindow::BackgroundWindow(QWidget *parent) : QWidget(parent) {
	timer_ = new QTimer();
	timer_->setInterval(500);
	connect(timer_, &QTimer::timeout, [this](){
		repaint();
	});
	timer_->start();
}

BackgroundWindow::~BackgroundWindow() {

}

void BackgroundWindow::load(const QSize& size, const QString& basicPath, const QString& playingPath, const QString& gameStartPath, const QString& gameEndPath) {
	playingImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), playingPath).absoluteFilePath());
	basicImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), basicPath).absoluteFilePath());
	gameStartImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), gameStartPath).absoluteFilePath());
	gameEndImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), gameEndPath).absoluteFilePath());

	windowsSize_ = size;
	resize(windowsSize_.width(), windowsSize_.height());

	setFocus();
}

void BackgroundWindow::setIsPlaying(const bool isPlaying) {
	isPlaying_ = !isPlaying_;
	//repaint();
}

void BackgroundWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	if (isPlaying_) {
		painter.drawImage(QPoint(0, 0), playingImage_.scaled(windowsSize_));
	}
	else {
		painter.drawImage(QPoint(0, 0), basicImage_.scaled(windowsSize_));

		painter.drawImage(QPoint((windowsSize_.width() - windowsSize_.width() / 5) / 2,
			windowsSize_.height() / 2 + (windowsSize_.height() / 10) * 2),
			gameStartImage_.scaled(QSize(windowsSize_.width() / 5, windowsSize_.height() / 10)));

		painter.drawImage(QPoint((windowsSize_.width() - windowsSize_.width() / 5) / 2,
			windowsSize_.height() / 2 + (windowsSize_.height() / 10) * 3),
			gameEndImage_.scaled(QSize(windowsSize_.width() / 5, windowsSize_.height() / 10)));
	}
}

void BackgroundWindow::keyPressEvent(QKeyEvent *event) {
	isPlaying_ = !isPlaying_;
}