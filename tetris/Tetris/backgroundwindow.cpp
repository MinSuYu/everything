#include "stdafx.h"
#include "backgroundwindow.h"

BackgroundWindow::BackgroundWindow(QWidget *parent) : QWidget(parent) {

}

BackgroundWindow::~BackgroundWindow() {

}

void BackgroundWindow::load(const QSize& size, const QString& basicPath, const QString& playingPath) {
	basicImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), basicPath).absoluteFilePath());
	playingImage_.load(QFileInfo(QCoreApplication::applicationDirPath(), playingPath).absoluteFilePath());

	resize(size.width(), size.height());
}

void BackgroundWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	QImage image = basicImage_;
	painter.drawImage(QPoint(0, 0), image);
}