#include "stdafx.h"
#include "lotto.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Lotto lotto;
	lotto.start();

	return a.exec();
}
