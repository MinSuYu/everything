#include "stdafx.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	const QString configPath = QString("config.ini");
	QFileInfo fi(QCoreApplication::applicationDirPath(), configPath);
	ConfigInstance().loadConfig(fi.absoluteFilePath());

	std::unique_ptr<MainWindow> mainWnd;
	mainWnd = std::make_unique<MainWindow>();

	return a.exec();
}
