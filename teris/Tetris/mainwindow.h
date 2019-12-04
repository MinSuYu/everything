#pragma once

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
public:
	MainWindow();
	~MainWindow();

private:
	Ui::MainWindow ui_;
};
