#pragma once

class BackgroundWindow : public QWidget {
	Q_OBJECT
public:
	BackgroundWindow(QWidget *parent);
	~BackgroundWindow();

public:
	void load(const QSize& size, const QString& basicPath, const QString& playingPath);

private:
	void paintEvent(QPaintEvent *event) override;

private:
	QImage basicImage_;
	QImage playingImage_;
};