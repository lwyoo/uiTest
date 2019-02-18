#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQuickItem>
#include <QQuickView>

class MainWindow : public QQuickView
{
    Q_OBJECT

public:
    static QSharedPointer<MainWindow> instance(QQuickView *parent=Q_NULLPTR);
    void findChiledItem(const QString objectName);
    void destroyTest(const QString objName);
    bool createComponent(const QString objectName, const qreal posX, const qreal posY);

    Q_INVOKABLE void upOpacity();
    Q_INVOKABLE void downOpacity();

private:
    explicit MainWindow(QQuickView *parent = nullptr );

// test code
signals:
    void testSignal(QString, qreal, qreal);

public slots:
    void testSlot(QString ob, qreal posX, qreal posY);


};

#endif // MAINWINDOW_H
