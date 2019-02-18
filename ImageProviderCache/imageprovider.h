#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QThread>


class ImageLoader : public QThread
{
    Q_OBJECT

public:
    ImageLoader(QObject *parent = Q_NULLPTR);
    ~ImageLoader();

protected:
    void run();

};

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};


#endif // IMAGEPROVIDER_H
