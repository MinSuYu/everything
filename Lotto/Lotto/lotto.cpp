#include "stdafx.h"
#include "lotto.h"

#include <iostream>

Lotto::Lotto() {
	lottoApiFormat_ = QString("https://www.nlotto.co.kr/common.do?method=getLottoNumber&drwNo=%1");
}

Lotto::~Lotto() {

}

void Lotto::start() {
	for (int i = 1; i < 2; i++) {
		QString lottoApiUrl = lottoApiFormat_.arg(i);

		QByteArray temp = requestNetwork(lottoApiUrl);
	}
}

QByteArray Lotto::requestNetwork(const QString& url) {
	QByteArray byteArray;
	QNetworkRequest request(url);
	//request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	QNetworkReply* reply = nullptr;
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	
	reply = manager->get(request);

	connect(reply, &QNetworkReply::finished, [this, reply, manager]{
		if (reply) {
			//QString temp = QString(reply->readAll());
			std::cout << reply->readAll().data() << std::endl;
			reply->deleteLater();
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

	return byteArray;
}