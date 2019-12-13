#include "stdafx.h"
#include "cardwidget.h"

CardWidget::CardWidget(QWidget *parent) : QWidget(parent) {
	animation_ = new QPropertyAnimation(this, "geometry");
	setStyleSheet("border: 1px solid black");
}

void CardWidget::load(const QString& path, const QString& backPath) {
	image_.load(path);
	backImage_.load(backPath);

	resize(image_.size().width() + 2, image_.size().height() + 2);
}

void CardWidget::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	QImage image = isFront_ ? image_ : backImage_;
	painter.drawImage(QPoint(1, 1), image);
}

void CardWidget::mousePressEvent(QMouseEvent *event) {

}

void CardWidget::mouseReleaseEvent(QMouseEvent *event) {
	emit clicked();
}

void CardWidget::moveA(int x, int y) {
	animation_->setDuration(500);
	animation_->setStartValue(geometry());
	animation_->setEndValue(QRect(x, y, width(), height()));

	animation_->start();
}