#include "stdafx.h"
#include "lotto.h"

#include <iostream>

Lotto::Lotto() {
	lottoApiFormat_ = QString("https://www.nlotto.co.kr/common.do?method=getLottoNumber&drwNo=%1");
}

Lotto::~Lotto() {

}

void Lotto::start() {
	for (int i = 1; i < 820; i++) {
		QString lottoApiUrl = lottoApiFormat_.arg(i);
		QByteArray byteArray = requestNetwork(lottoApiUrl);
		std::cout << byteArray.data() << std::endl;
	}
	std::cout << "end" << std::endl;
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