#pragma once

class CardWidget : public QWidget {
	Q_OBJECT
public:
	CardWidget(QWidget *parent);

	void load(const QString& path, const QString& backPath);
	void showFront(bool front) {
		isFront_ = front;
	}
	bool isFront() const {
		return isFront_;
	}

signals:
	void clicked();

private:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

public:
	void moveA(int x, int y);

private:
	QImage image_;
	QImage backImage_;
	bool isFront_ = true;

	QPointer<QPropertyAnimation> animation_;
};