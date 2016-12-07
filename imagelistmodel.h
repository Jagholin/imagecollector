#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QImage>

struct ImageMetaData {
    QString imageAddress;
    QImage imageData;
    bool imageSaved;
    enum {
        CORRECT_CLASS, INCORRECT_CLASS, UNKNOWN_CLASS
    } imageClassifierStatus;
    QString imageClassifier;
};

class ImageListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ImageDataRoles {
        ImageAddressRole = Qt::UserRole + 1,
        ImageDataRole,
        ImageSavedRole,
        ImageClassifierStatusRole,
        ImageClassifierRole
    };

    explicit ImageListModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Functions used by ImageProvider
    QString getImageAddress(unsigned int index);

public slots:
    int addNewImageData(QString imageAddress, QString keyword);
    void setImageAtIndex(unsigned int index, QImage const& image);
    void imageAtIndex(unsigned int index, int responseid) const;

signals:
    void imageReply(QImage img, int responseid) const;

private:
    QVector<ImageMetaData> m_imageData;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // IMAGELISTMODEL_H
