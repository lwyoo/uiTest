#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQuickItem>
#include <QQuickView>

class MainWindow : public QQuickView
{
    Q_OBJECT

public:
    static QSharedPointer<MainWindow> instance(QQuickView *parent=Q_NULLPTR);

    void checkoutChiledItem(const QString objName);




private:
    explicit MainWindow(QQuickView *parent = nullptr );


};

#endif // MAINWINDOW_H
