#include "stdafx.h"
#include "lotto.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//lottoapiserver::LottoApiServer test;

	Lotto lotto;
	lotto.start();

	return a.exec();
}
