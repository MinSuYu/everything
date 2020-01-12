#include "stdafx.h"
#include "lotto.h"

#include <iostream>

Lotto::Lotto() {
	lottoApiFormat_ = QString("https://www.nlotto.co.kr/common.do?method=getLottoNumber&drwNo=%1");

	if (QSslSocket::supportsSsl()) {
		qDebug() << QSslSocket::sslLibraryBuildVersionString();
		qDebug() << "support";
	}
	else {
		qDebug() << QSslSocket::sslLibraryBuildVersionString();
		qDebug() << "not support";
	}
}

Lotto::~Lotto() {

}

void Lotto::start() {
	for (int i = 1; i < 2; i++) {
		lottoApiUrl_ = lottoApiFormat_.arg(i);

		QByteArray temp = requestNetwork(lottoApiUrl_);
	}
}

void Lotto::test(const QString& url) {
	QSslSocket socket;
	socket.connectToHostEncrypted(url, 443);
	socket.write("GET / HTTP/1.0\r\n\r\n");
	while (socket.waitForReadyRead())
		std::cout << socket.readAll().data() << std::endl;
}

QByteArray Lotto::requestNetwork(const QString& url) {
	QByteArray byteArray;
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
	//request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
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

QByteArray Lotto::syncNetworkRequest(const QString& url) {
	QByteArray byteArray;
	QNetworkRequest request(url);
	QNetworkAccessManager* manager = new QNetworkAccessManager();
	QNetworkReply* reply = manager->get(request);
	QEventLoop loop;

	connect(reply, &QIODevice::readyRead, [this, reply, &byteArray] {
		byteArray += reply->readAll();
	});

	connect(reply, &QNetworkReply::finished, [this, &loop] {
		loop.exit();
	});

	connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [this, reply, &byteArray, &loop](QNetworkReply::NetworkError) {
		qDebug() << "error" << reply->errorString();
		qDebug() << "received" << byteArray;
		byteArray.clear();
		loop.exit();
	});

	loop.exec();
	reply->deleteLater();
	manager->deleteLater();

	return byteArray;
}