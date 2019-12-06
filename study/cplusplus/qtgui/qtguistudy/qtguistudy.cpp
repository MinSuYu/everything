#include "stdafx.h"
#include "qtguistudy.h"
#include <QtWidgets>
#include <moduleinterface\/inc/plugininterface.h>

typedef ModuleInterface* (*CreateModule)();

qtguistudy::qtguistudy(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.loadModuleBtn, &QPushButton::clicked, [this]() {
		QString pathName = QFileDialog::getOpenFileName(this, "load");
		QLibrary lib(pathName);

		bool ret = lib.load();
		if (!ret) {
			QMessageBox::critical(this, "failed", "failed");
			return;
		}

		CreateModule factory = (CreateModule)lib.resolve("createModule");
		if (!factory) {
			QMessageBox::critical(this, "failed", "failed");
			return;
		}

		ModuleInterface* intr = factory();

		ui.editRace->setText(intr->race());
		ui.editType->setText(intr->type());
		ui.editName->setText(intr->name());
		ui.editMove->setText(intr->move());
		ui.editAttack->setText(intr->attack());
		ui.editStop->setText(intr->stop());
	});
}
