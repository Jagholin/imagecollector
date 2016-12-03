#include "googleloader.h"

GoogleLoader::GoogleLoader(QObject* parent):
    QObject(parent),
    m_googleManager(new QNetworkAccessManager(this))
{
}

void GoogleLoader::onReplyLoaded()
{
    QNetworkReply* myReply = qobject_cast<QNetworkReply*>(sender());

    QByteArray response = myReply->readAll();
    QString responseStr (response);

    responseStr += "\nHeader pairs: \n";
    QList<QByteArray> headerLists = myReply->rawHeaderList();
    foreach (QByteArray header, headerLists) {
        responseStr += QString(header) + ": " + myReply->rawHeader(header) + "\n";
    }

    bool disconnectSuccessful = disconnect(myReply, 0, this, 0);
    Q_ASSERT(disconnectSuccessful);
    myReply->deleteLater();
    emit hereYouGo(responseStr);
}

void GoogleLoader::searchFor(QString keyword)
{
    QUrlQuery myQuery;
    myQuery.addQueryItem("q", keyword);
    myQuery.addQueryItem("tbm", "isch");
    QUrl myUrl(QString("http://www.google.com/search"));
    myUrl.setQuery(myQuery);
    QNetworkRequest myRequest(myUrl);

    myRequest.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    QNetworkReply* reply = m_googleManager->get(myRequest);

    connect(reply, SIGNAL(finished()), this, SLOT(onReplyLoaded()));
}
