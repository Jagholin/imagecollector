#ifndef GOOGLELOADER_H
#define GOOGLELOADER_H

#include <QQuickItem>
#include <QtNetwork>

class GoogleLoader : public QObject
{
    Q_OBJECT
public:
    GoogleLoader(QObject* parent = nullptr);

protected:
    QNetworkAccessManager* m_googleManager;
    //QNetworkReply* m_reply;
signals:
    void newPictureUrl(QString pictureUrl);

public slots:
    void onReplyLoaded();
    void searchFor(QString keyword, QString engineId, QString apiKey);
};

#endif // GOOGLELOADER_H
