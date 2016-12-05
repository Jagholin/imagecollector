#ifndef GOOGLEIMAGEPROVIDER_H
#define GOOGLEIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QNetworkAccessManager>

class ImageListModel;

class GoogleImageProvider : public QQuickImageProvider
{
public:
    GoogleImageProvider(ImageListModel* imageList);

    // QQmlImageProviderBase interface
public:
    ImageType imageType() const override;

    // QQuickImageProvider interface
public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

protected:
    QNetworkAccessManager m_imageLoader;
    ImageListModel* m_imageList;
};

#endif // GOOGLEIMAGEPROVIDER_H
