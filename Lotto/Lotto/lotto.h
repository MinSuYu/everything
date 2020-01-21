#pragma once
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

#include <QJsonDocument>
#include <QJsonObject>

class Lotto : public QObject {
public:
	Lotto();
	~Lotto();

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