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
    explicit GoodsShowItem(Goods* g, int count);
    ~GoodsShowItem();

private:
    Ui::GoodsShowItem *ui;
};

#endif // GOODSSHOWITEM_H
