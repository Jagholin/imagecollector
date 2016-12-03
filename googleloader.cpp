#include "googleloader.h"

GoogleLoader::GoogleLoader(QObject* parent):
    QObject(parent),
    m_googleManager(new QNetworkAccessManager(this))
{
    QNetworkRequest myRequest(QUrl("http://www.google.com/search?q=dog"));
    myRequest.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    m_reply = m_googleManager->get(myRequest);

    connect(m_reply, SIGNAL(finished()), this, SLOT(onReplyLoaded()));
}

void GoogleLoader::onReplyLoaded()
{
    QByteArray response = m_reply->readAll();
    QString responseStr (response);

    responseStr += "\nHeader pairs: \n";
    QList<QByteArray> headerLists = m_reply->rawHeaderList();
    foreach (QByteArray header, headerLists) {
        responseStr += QString(header) + ": " + m_reply->rawHeader(header) + "\n";
    }

    emit hereYouGo(responseStr);
}
