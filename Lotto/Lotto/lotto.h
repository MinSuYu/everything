#pragma once
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QSslConfiguration>

class Lotto : public QObject {
public:
	Lotto();
	~Lotto();

public:
	void start();
	QByteArray syncNetworkRequest(const QString& url);
	QByteArray requestNetwork(const QString& url);
	void test(const QString& url);

private:
	QString lottoApiFormat_;
	QString lottoApiUrl_;
};