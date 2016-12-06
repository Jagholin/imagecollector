#ifndef GOOGLEIMAGEPROVIDER_H
#define GOOGLEIMAGEPROVIDER_H

#include <QQuickImageResponse>
#include <QQuickAsyncImageProvider>
#include <QNetworkAccessManager>

class ImageListModel;

class AsyncImageResponse : public QQuickImageResponse
{
    Q_OBJECT
public:
    // QQuickImageResponse interface
public:
    explicit AsyncImageResponse(QNetworkRequest req, QSize const& requestedSize, ImageListModel* imageList, int index);
    QQuickTextureFactory *textureFactory() const override;

public slots:
    void onResponseFinished();

protected:
    QNetworkAccessManager m_imageLoader;
    QNetworkReply* m_reply;
    QSize m_requestedSize;
    ImageListModel* m_imageList;
    QImage m_resultImage;
    int m_index;
};

class GoogleImageProvider : public QQuickAsyncImageProvider
{
public:
    GoogleImageProvider(ImageListModel* imageList);

protected:
    ImageListModel* m_imageList;

    // QQuickAsyncImageProvider interface
public:
    QQuickImageResponse *requestImageResponse(const QString &id, const QSize &requestedSize) override;
};

#endif // GOOGLEIMAGEPROVIDER_H
