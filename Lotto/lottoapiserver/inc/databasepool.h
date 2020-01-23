#pragma once

namespace lottoapiserver {
	class DatabasePool {
	public:
		DatabasePool();
		~DatabasePool();

	public:
		bool open(const QString& databaseName);
		void close();

		void releaseConnection();
		void newConnection();

	public:
		QSqlDatabase database();

	private:
		QMutex mutex_;
		bool isExecFlag_ = false;

		QSqlDatabase database_;
	};

	typedef std::shared_ptr<DatabasePool> DatabasePoolPtr;
}