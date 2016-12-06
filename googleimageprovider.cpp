#include "googleimageprovider.h"
#include "imagelistmodel.h"
#include <QtNetwork>

AsyncImageResponse::AsyncImageResponse(QNetworkRequest req, QSize const& reqSize, ImageListModel* imageList, int index)
{
    m_reply = m_imageLoader.get(req);
    m_requestedSize = reqSize;
    m_imageList = imageList;
    m_index = index;

    qDebug() << "Waiting for image request";

    connect(m_reply, &QNetworkReply::finished, this, &AsyncImageResponse::onResponseFinished);
}

void AsyncImageResponse::onResponseFinished()
{
    QByteArray myImageData = m_reply->readAll();

    m_resultImage = QImage::fromData(myImageData);
    //*size = resultImage.size();

    qDebug() << "Image loaded";
    m_imageList->setImageAtIndex(m_index, m_resultImage);
    if (m_requestedSize.isValid())
    {
        m_resultImage = m_resultImage.scaled(m_requestedSize);
    }
    //return resultImage;
    emit finished();
}

QQuickTextureFactory *AsyncImageResponse::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(m_resultImage);
}

GoogleImageProvider::GoogleImageProvider(ImageListModel* imageList):
    m_imageList(imageList)
{
}

QQuickImageResponse* GoogleImageProvider::requestImageResponse(const QString &id, const QSize &requestedSize)
{
    QNetworkRequest myRequest(QUrl(m_imageList->getImageAddress(id.toInt())));

    return new AsyncImageResponse(myRequest, requestedSize, m_imageList, id.toInt());
}
