#ifndef MYQUICKITEM_H
#define MYQUICKITEM_H

#include <QQuickItem>
class MyQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    static QSharedPointer<MyQuickItem> instance(QQuickItem *parent=Q_NULLPTR);
    void destroyTest();
    ~MyQuickItem();




private:
    explicit MyQuickItem(QQuickItem *parent=Q_NULLPTR);

    QQuickItem* mItem;

};

#endif // MYQUICKITEM_H
