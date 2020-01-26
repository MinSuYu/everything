#pragma once

#include "networkdata_global.h"

namespace networkdata {
	class NETWORKDATA_EXPORT NetworkData : public QObject {
	public:
		NetworkData();
		~NetworkData();

	public:
		void start();
		QByteArray requestNetwork(const QString& url);
		bool parsingData(const QByteArray& data);

	private:
		QString lottoApiFormat_;
		bool isContinue_ = true;
		QList<QVector<int>> numberList_;
		QVector<int> numberCount_;
	};
}
