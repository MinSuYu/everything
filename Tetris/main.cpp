#include "stdafx.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//QPointer<MainWindow> mainWnd;
	//mainWnd = new MainWindow();

	const QString configPath = QString("config.ini");
	ConfigInstance().loadConfig(configPath);

	return a.exec();
}
