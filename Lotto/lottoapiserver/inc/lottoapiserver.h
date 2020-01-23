#pragma once

#include "databasepool.h"

namespace lottoapiserver {
	class LottoApiServer {
	public:
		LottoApiServer();
		~LottoApiServer();

	private:
		DatabasePoolPtr databasePoolPtr_;
	};
}