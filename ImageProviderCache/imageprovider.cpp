#include "imageprovider.h"
#include <QThread>
#include <QDebug>
#include <QPixmapCache>


ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    new ImageLoader;
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    //    Q_UNUSED(id);

    qDebug() << QThread::currentThread() << Q_FUNC_INFO << id;

    QPixmap pm;

    if (!QPixmapCache::find(id, pm)) {
        qDebug() << "find false";
        pm.load("/home/ooo/ImageProviderCache/"+id+".jpg", "JPEG");
        QPixmapCache::insert(id, pm);
    }

    return pm;
}

ImageLoader::ImageLoader(QObject *parent)
    : QThread (parent)
{
    start(LowestPriority);
}

ImageLoader::~ImageLoader()
{

}

void ImageLoader::run()
{
    QPixmap pm;

    qDebug() << QPixmapCache::cacheLimit();
    QPixmapCache::setCacheLimit(800000);
    qDebug() << QPixmapCache::cacheLimit();

    if (!QPixmapCache::find("1", pm)) {

        qDebug() << pm.load("/home/ooo/ImageProviderCache/1.jpg", "JPEG");
        qDebug() << QPixmapCache::insert("1", pm);
    }

    if (!QPixmapCache::find("2", pm)) {
        qDebug() << pm.load("/home/ooo/ImageProviderCache/2.jpg", "JPEG");
        qDebug() << QPixmapCache::insert("2", pm);
    }

    if (!QPixmapCache::find("3", pm)) {
        qDebug() << pm.load("/home/ooo/ImageProviderCache/3.jpg", "JPEG");
        qDebug() << QPixmapCache::insert("3", pm);
    }

    if (!QPixmapCache::find("4", pm)) {
        qDebug() << pm.load("/home/ooo/ImageProviderCache/4.jpg", "JPEG");
        qDebug() << QPixmapCache::insert("4", pm);
    }



    qDebug() << "image load completed!!!";

    this->deleteLater();
}
