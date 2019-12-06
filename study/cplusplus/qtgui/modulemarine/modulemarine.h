#pragma once

class ModuleMarine : public ModuleInterface 
{
	QString race() const override {
		return "Terran";
	}
	QString type() const override {
		return "bionic";
	}
	QString name() const override {
		return "marine";
	}
	QString move() const override {
		return "one step";
	}
	QString attack() const override {
		return "gun shot";
	}
	QString stop() const override {
		return "stop!!";
	}
};
