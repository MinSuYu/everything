#include "stdafx.h"
#include "backgroundwindow.h"

BackgroundWindow::BackgroundWindow(QWidget *parent) : QWidget(parent) {

}

BackgroundWindow::~BackgroundWindow() {

}

void BackgroundWindow::load(const QSize& size, const QString& basicPath, const QString& playingPath) {
	playingImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), playingPath).absoluteFilePath());
	basicImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), basicPath).absoluteFilePath());
	if (QFile(QFileInfo(QCoreApplication::applicationDirPath(), playingPath).absoluteFilePath()).exists()) {
		std::cout << "ok" << std::endl;
		if (playingImage_.isNull()) {
			std::cout << "null" << std::endl;
		}
	}
	else {
		std::cout << "no" << std::endl;
	}
	resize(size.width(), size.height());
}

void BackgroundWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	//QImage image = basicImage_;
	QImage image = isPlaying_ ? playingImage_ : basicImage_;
	painter.drawImage(QPoint(0, 0), image);
}