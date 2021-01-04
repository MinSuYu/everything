#include "stdafx.h"
#include "lotto.h"

#include <iostream>

Lotto::Lotto() {
	lottoApiFormat_ = QString("https://www.dhlottery.co.kr/common.do?method=getLottoNumber&drwNo=%1");
}

Lotto::~Lotto() {

}

void Lotto::start() {
	int count = 0;
	while (isContinue_) {
		QString lottoApiUrl = lottoApiFormat_.arg(++count);
		QByteArray byteArray = requestNetwork(lottoApiUrl);
		isContinue_ = parsingData(byteArray);

		std::cout << "ing... count : " << count << std::endl;
	}
	numberCount_.resize(45);
	std::cout << "end count : " << count << std::endl;
	for (int i = 0; i < numberList_.size(); i++) {
		QVector<int> oneTimeNumber = numberList_.value(i);
		qDebug() << "count : " << i + 1 << " , " << oneTimeNumber;
		for (int j = 0; j < 6; j++) {
			numberCount_[oneTimeNumber[j] - 1]++;
		}
	}

	for (int i = 0; i < numberCount_.size(); i++) {
		std::cout << i + 1 << " : " << numberCount_[i] << ", ";
		if ((i % 5) == 0) {
			std::cout << std::endl;
		}
	}
}

QByteArray Lotto::requestNetwork(const QString& url) {
	QByteArray byteArray;
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
	QNetworkReply* reply = nullptr;
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	QEventLoop eventLoop;
	
	reply = manager->get(request);

	connect(reply, &QNetworkReply::finished, [this, reply, manager, &byteArray, &eventLoop]{
		if (reply) {
			byteArray = reply->readAll();
			reply->deleteLater();
			eventLoop.exit();
		}

		if (manager) {
			manager->deleteLater();
		}
	});

	connect(reply,
		static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
		[this, reply, manager](QNetworkReply::NetworkError err) {
		qDebug() << "Request error:" << err;
		reply->ignoreSslErrors();

		if (reply) {
			reply->deleteLater();
		}

		if (manager) {
			manager->deleteLater();
		}
	});

	eventLoop.exec();
	return byteArray;
}

bool Lotto::parsingData(const QByteArray& data) {
	QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

	if (!jsonDocument.isNull()) {
		QJsonObject rootObject = jsonDocument.object();
		if (!rootObject.isEmpty()) {
			if (rootObject.value("returnValue").toString().compare("fail")) {
				QVector<int> parsingNumberList;
				parsingNumberList.resize(7);
				parsingNumberList[0] = rootObject.value("drwtNo1").toInt();
				parsingNumberList[1] = rootObject.value("drwtNo2").toInt();
				parsingNumberList[2] = rootObject.value("drwtNo3").toInt();
				parsingNumberList[3] = rootObject.value("drwtNo4").toInt();
				parsingNumberList[4] = rootObject.value("drwtNo5").toInt();
				parsingNumberList[5] = rootObject.value("drwtNo6").toInt();
				parsingNumberList[6] = rootObject.value("bnusNo").toInt();
				numberList_.push_back(parsingNumberList);
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}

	return true;
}