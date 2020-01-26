#include "stdafx.h"
#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	networkdata::NetworkData networkData;
	std::cout << "main" << std::endl;
	networkData.start();

	return a.exec();
}
