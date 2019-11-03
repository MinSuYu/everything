#include <QtCore/QCoreApplication>

#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	std::cout << QString("test").toUtf8().data() << std::endl;

	return a.exec();
}
