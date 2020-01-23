#include "stdafx.h"
#include "../inc/lottoapiserver.h"

namespace lottoapiserver {
	LottoApiServer::LottoApiServer() {
		//databasePoolPtr_ = std::make_shared<DatabasePool>();
		//databasePoolPtr_->open("");
		qDebug() << "test";
	}

	LottoApiServer::~LottoApiServer() {
		//databasePoolPtr_->close();
	}
}