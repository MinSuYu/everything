#include "stdafx.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	const QString configPath = QString("./config.ini");
	ConfigInstance().loadConfig(configPath);

	std::unique_ptr<MainWindow> mainWnd;
	mainWnd = std::make_unique<MainWindow>();

	return a.exec();
}
