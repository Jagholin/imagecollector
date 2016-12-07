#include "googleimageprovider.h"
#include "imagelistmodel.h"
#include <QtNetwork>
#include <functional>

QAtomicInt AsyncImageResponse::s_objectCounter = 0;

AsyncImageResponse::AsyncImageResponse(QNetworkRequest req, QSize const& reqSize, ImageListModel* imageList, int index)
{
    m_imageResponseId = s_objectCounter.fetchAndAddRelaxed(1);
    qDebug() << "async image response created id = " << m_imageResponseId;

    connect(this, &AsyncImageResponse::requestImageAtIndex, imageList, &ImageListModel::imageAtIndex, Qt::QueuedConnection);
    connect(imageList, &ImageListModel::imageReply, this, &AsyncImageResponse::onImageModelReply);
    m_threadOwner = QThread::currentThread();
    m_request = req;
    m_imageList = imageList;
    m_index = index;
    m_requestedSize = reqSize;
    emit requestImageAtIndex(index, m_imageResponseId);
}

void AsyncImageResponse::onImageModelReply(QImage img, int imageResponseId)
{
    if (imageResponseId != m_imageResponseId)
        return;

    qDebug() << "async image response id " << imageResponseId << " entry";

    Q_ASSERT(QThread::currentThread() == m_threadOwner);
    disconnect(m_imageList, &ImageListModel::imageReply, this, 0);
    if (! img.isNull())
    {
        m_resultImage = img;
        m_reply = nullptr;
        qDebug() << "fetching previous image";
        emit finished();
    }
    else
    {
        m_reply = m_imageLoader.get(m_request);
        qDebug() << "Waiting for image request";
        connect(m_reply, &QNetworkReply::finished, this, &AsyncImageResponse::onResponseFinished);
    }
}

void AsyncImageResponse::onResponseFinished()
{
    qDebug() << "on responsefinished id " << m_imageResponseId << "entry";

    Q_ASSERT(QThread::currentThread() == m_threadOwner);
    Q_ASSERT(m_reply);
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
    m_reply->deleteLater();
    m_reply = nullptr;
    emit finished();
}

QQuickTextureFactory *AsyncImageResponse::textureFactory() const
{
    Q_ASSERT(QThread::currentThread() == m_threadOwner);
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
