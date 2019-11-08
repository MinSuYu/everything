#include "stdafx.h"

int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);
	QApplication a(argc, argv);

	std::cout << QString("test").toUtf8().data() << std::endl;
	QPointer<MainWindow> mainWnd;
	mainWnd = new MainWindow();

	return a.exec();
}
