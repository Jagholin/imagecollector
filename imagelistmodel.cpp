#include "imagelistmodel.h"

ImageListModel::ImageListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant ImageListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    return QAbstractListModel::headerData(section, orientation, role);
}

int ImageListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_imageData.size();
}

QVariant ImageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ImageMetaData data = m_imageData.at(index.row());
    if (role == ImageAddressRole)
        return QVariant(data.imageAddress);
    if (role == ImageDataRole)
        return QVariant(data.imageData);
    if (role == ImageSavedRole)
        return QVariant(data.imageSaved);
    if (role == ImageClassifierStatusRole)
        return QVariant(data.imageClassifierStatus);
    if (role == ImageClassifierRole)
        return QVariant(data.imageClassifier);

    return QVariant();
}

void ImageListModel::setImageAtIndex(unsigned int index, const QImage &image)
{
    m_imageData[index].imageData = image;
    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

QString ImageListModel::getImageAddress(unsigned int index)
{
    return m_imageData[index].imageAddress;
}

int ImageListModel::addNewImageData(QString imageAddress, QString keyword)
{
    beginInsertRows(QModelIndex(), m_imageData.size(), m_imageData.size());

    ImageMetaData newData;
    newData.imageAddress = imageAddress;
    newData.imageClassifierStatus = ImageMetaData::UNKNOWN_CLASS;
    newData.imageClassifier = keyword;
    newData.imageSaved = false;

    m_imageData.push_back(newData);
    endInsertRows();
    return m_imageData.size() - 1;
}


QHash<int, QByteArray> ImageListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(ImageAddressRole, "address");
    names.insert(ImageDataRole, "image");
    names.insert(ImageSavedRole, "isSaved");
    names.insert(ImageClassifierStatusRole, "classifierStatus");
    names.insert(ImageClassifierRole, "classifier");
    return names;
}
