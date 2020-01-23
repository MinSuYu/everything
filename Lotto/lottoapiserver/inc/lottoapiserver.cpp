#include "stdafx.h"
#include "lottoapiserver.h"

namespace lottoapiserver {
	LottoApiServer::LottoApiServer() {
		databasePoolPtr_ = std::make_shared<DatabasePool>();
		databasePoolPtr_->open("");
	}

	LottoApiServer::~LottoApiServer() {
		databasePoolPtr_->close();
	}
}