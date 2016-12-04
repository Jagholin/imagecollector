#include "googleloader.h"
#include <QRegularExpression>
#include <QJsonDocument>
#include <QFile>

GoogleLoader::GoogleLoader(QObject* parent):
    QObject(parent),
    m_googleManager(new QNetworkAccessManager(this))
{
}

void GoogleLoader::onReplyLoaded()
{
    QNetworkReply* myReply = qobject_cast<QNetworkReply*>(sender());

    qDebug() << myReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    QByteArray response = myReply->readAll();

    QFile debugFile("debug.txt");
    debugFile.open(QIODevice::WriteOnly | QIODevice::Text);
    debugFile.write(response);
    debugFile.close();

    QJsonDocument replyParser = QJsonDocument::fromJson(response);
    QJsonObject searchResults = replyParser.object();
    QJsonArray searchItems = searchResults.value("items").toArray();
    for (QJsonValue item: searchItems)
    {
        QJsonObject searchItem = item.toObject();
        emit newPictureUrl(searchItem.value("link").toString());
    }

    bool disconnectSuccessful = disconnect(myReply, 0, this, 0);
    Q_ASSERT(disconnectSuccessful);
    myReply->deleteLater();
    //emit hereYouGo(responseStr);
}

void GoogleLoader::searchFor(QString keyword, QString engineId, QString apiKey)
{
    QUrlQuery myQuery;

    QUrl myUrl(QString("https://www.googleapis.com/customsearch/v1"));
    myQuery.addQueryItem("q", keyword);
    myQuery.addQueryItem("filter", "0");
    myQuery.addQueryItem("searchType", "image");
    myQuery.addQueryItem("cx", engineId);
    myQuery.addQueryItem("key", apiKey);
    myUrl.setQuery(myQuery);

    qDebug() << "Sending request url: " << myUrl.toDisplayString();
    QNetworkRequest myRequest(myUrl);

    myRequest.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    QNetworkReply* reply = m_googleManager->get(myRequest);

    connect(reply, SIGNAL(finished()), this, SLOT(onReplyLoaded()));
}
