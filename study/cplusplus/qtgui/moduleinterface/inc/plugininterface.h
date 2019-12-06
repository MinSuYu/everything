#pragma once

#include <QtCore>

 class ModuleInterface {
 public:
	 virtual QString race() const abstract;
	 virtual QString type() const abstract;
	 virtual QString name() const abstract;
	 virtual QString move() const abstract;
	 virtual QString attack() const abstract;
	 virtual QString stop() const abstract;
};