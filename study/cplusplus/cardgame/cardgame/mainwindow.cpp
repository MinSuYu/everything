#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui_.setupUi(this);

	card_ = new CardWidget(ui_.centralWidget);
	card_->load(":/CardImage/Resources/images/1.png", ":/CardImage/Resources/images/0.png");
	card_->update();

	connect(card_, &CardWidget::clicked, [this]{
		card_->showFront(!card_->isFront());
		//card_->moveA(200, 200);
		card_->update();
	});
}
