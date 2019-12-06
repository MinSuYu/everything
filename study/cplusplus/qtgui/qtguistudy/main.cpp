#include "stdafx.h"
#include "qtguistudy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qtguistudy w;
	w.show();
	return a.exec();
}
