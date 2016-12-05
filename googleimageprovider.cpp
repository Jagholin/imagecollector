#include "googleimageprovider.h"
#include "imagelistmodel.h"
#include <QtNetwork>

GoogleImageProvider::GoogleImageProvider(ImageListModel* imageList):
    m_imageList(imageList), QQuickImageProvider(QQmlImageProviderBase::Image)
{
}

QQmlImageProviderBase::ImageType GoogleImageProvider::imageType() const
{
    return QQmlImageProviderBase::Image;
}

QImage GoogleImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QNetworkRequest myRequest(QUrl(m_imageList->getImageAddress(id.toInt())));
    QNetworkReply* myReply = m_imageLoader.get(myRequest);
    QByteArray myImageData;
    while (!myReply->isFinished())
    {
        if (! myReply->waitForReadyRead(-1))
            return QImage();
        myImageData += myReply->readAll();
    }
    Q_ASSERT(myReply->isFinished() && myReply->bytesAvailable() == 0);
    QImage resultImage = QImage::fromData(myImageData);
    *size = resultImage.size();

    m_imageList->setImageAtIndex(id.toInt(), resultImage);
    if (requestedSize.isValid())
    {
        return resultImage.scaled(requestedSize);
    }
    return resultImage;
}
