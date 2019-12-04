#include "stdafx.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	const QString configPath = QString("config.ini");
	ConfigInstance().loadConfig(configPath);

	QPointer<MainWindow> mainWnd;
	mainWnd = new MainWindow();

	return a.exec();
}
