#pragma once

#include "ui_mainwindow.h"
#include "backgroundwindow.h"

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	void keyPressEvent(QKeyEvent *event) override;

private:
	Ui::MainWindow ui_;

	std::unique_ptr<BackgroundWindow> backgroundWindow_;
};
