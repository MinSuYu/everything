#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui_.setupUi(this);

	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QDesktopWidget* desktopWidget = QApplication::desktop();

	QRect rect = desktopWidget->screenGeometry(0);

	this->setFixedSize(rect.width() / 2, rect.height() / 2);
	this->move(rect.center() / 2);

	backgroundWindow_ = std::make_unique<BackgroundWindow>(ui_.centralWidget);
	backgroundWindow_->load(QSize(rect.width() / 2, rect.height() / 2), ConfigInstance().basicBackGroundImagePath(), ConfigInstance().playingBackGroundImagePath());
	
	show();
}

MainWindow::~MainWindow()
{
}
