#include "stdafx.h"

MainWindow::MainWindow()
{
	ui_.setupUi(this);

	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QDesktopWidget* desktopWidget = QApplication::desktop();

	QRect rect = desktopWidget->screenGeometry(0);

	this->setFixedSize(rect.width() / 2, rect.height() / 2);
	this->move(rect.center() / 2);
	this->setAttribute(Qt::WA_TranslucentBackground);

	QImage image(QFileInfo(QCoreApplication::applicationDirPath(), "./basicimage.png").absoluteFilePath());
	QPixmap pixmap = QPixmap::fromImage(image);

	ui_.backgroundLabel->setPixmap(pixmap);
	ui_.backgroundLabel->move(0, 0);
	ui_.backgroundLabel->resize(this->width(), this->height());
	
	show();
}

MainWindow::~MainWindow()
{
}
