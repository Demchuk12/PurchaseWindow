#ifndef GOODSSHOWITEM_H
#define GOODSSHOWITEM_H

#include <QWidget>
#include <goods.h>
namespace Ui {
class GoodsShowItem;
}

class GoodsShowItem : public QWidget
{
    Q_OBJECT


    Goods* goods;
    QPair<QByteArray, QString> rest;

public:
    int currentCount =0;
    float currentPrice = 0;
     int Plase = 0;
    explicit GoodsShowItem(Goods* g, int count, int Plase);
    ~GoodsShowItem();
     int getID(){
         return goods->ID;
     }

signals:
    void mousePressEvent(QMouseEvent *event);
    void edit(Goods* goods);
    void dell(int ID);
private slots:
    void startEdit();
    void startDell();
    void ShowContextMenu(const QPoint &pos);
private:
    Ui::GoodsShowItem *ui;
};

#endif // GOODSSHOWITEM_H
