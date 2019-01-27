#include "goodsshowitem.h"
#include "ui_goodsshowitem.h"

GoodsShowItem::GoodsShowItem(Goods* g, int count):QWidget(nullptr),
    goods(g),
    ui(new Ui::GoodsShowItem)
{
    ui->setupUi(this);
    if(count == 0)
        ui->Count->hide();
    else
        ui->Count->setText(QString().number(count)+ " шт.");

    ui->Name->setText(goods->name);
    rest = goods->getRest();
    QPixmap* photo = new QPixmap();
    photo->loadFromData(rest.first);
    ui->Image->setAutoFillBackground(true);
    ui->Image->setPixmap(photo->scaled(128, 128));

}

GoodsShowItem::~GoodsShowItem()
{
    delete ui;
}
