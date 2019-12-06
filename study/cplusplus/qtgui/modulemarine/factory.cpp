#include "stdafx.h"
#include "factory.h"
#include "modulemarine.h"

ModuleInterface* createModule() {
	//return nullptr;
	return new ModuleMarine();
}