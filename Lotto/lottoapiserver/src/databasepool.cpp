#include "stdafx.h"
#include "../inc/databasepool.h"

namespace lottoapiserver {
	DatabasePool::DatabasePool() {

	}

	DatabasePool::~DatabasePool() {
	}
	
	bool DatabasePool::open(const QString& databaseName) {
		database_ = QSqlDatabase::addDatabase("QSQLITE");
		database_.setDatabaseName(databaseName);

		if(database_.open() == false) {
			return false;
		}

		return true;
	}

	void DatabasePool::close() {
		if (database_.isOpen() == true) {
			database_.close();
		}
	}

	void DatabasePool::releaseConnection() {
		isExecFlag_ = false;
	}

	void DatabasePool::newConnection() {
		QMutexLocker locker(&mutex_);

		while (isExecFlag_)
		{
			QThread::msleep(10);
		}

		isExecFlag_ = true;
	}

	QSqlDatabase DatabasePool::database() {
		return database_;
	}
}