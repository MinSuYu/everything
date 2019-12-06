#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtguistudy.h"

class qtguistudy : public QMainWindow
{
	Q_OBJECT

public:
	qtguistudy(QWidget *parent = Q_NULLPTR);

private:
	Ui::qtguistudyClass ui;
};
