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
	QByteArray requestNetwork(const QString& url);

private:
	QString lottoApiFormat_;
};