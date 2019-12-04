#include "stdafx.h"

MainWindow::MainWindow()
{
	ui_.setupUi(this);

	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QDesktopWidget* desktopWidget = QApplication::desktop();

	//int screenCount = desktopWidget->screenCount();
	QRect rect = desktopWidget->screenGeometry(0);

	this->setFixedSize(rect.width()/2, rect.height()/2);
	this->move(rect.center() / 2);
	
	show();
}

MainWindow::~MainWindow()
{
}
