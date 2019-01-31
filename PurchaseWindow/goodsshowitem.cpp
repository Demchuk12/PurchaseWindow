#include "goodsshowitem.h"
#include "ui_goodsshowitem.h"
#include <QMouseEvent>
#include <database.h>
#include <QMenu>
GoodsShowItem::GoodsShowItem(Goods* g, int count, int plase):
    QWidget(nullptr),
    goods(g),
    ui(new Ui::GoodsShowItem)
{
    ui->setupUi(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);


    connect(this, &GoodsShowItem::customContextMenuRequested, this, &GoodsShowItem::ShowContextMenu);

    Plase = plase;
    if(count == 0)
        ui->Count->setText(QString().number(goods->price));
    else{
        ui->Count->setText(QString().number(count)+ " шт.");
        currentCount = count;
    }
    currentPrice = count*goods->price;
    ui->Name->setText(goods->name);
    rest = goods->getRest();
    QPixmap* photo = new QPixmap();
    photo->loadFromData(rest.first);
    ui->Image->setAlignment(Qt::AlignCenter);

    ui->Image->setAutoFillBackground(true);
    ui->Image->setPixmap(photo->scaled(150, 150 ));

}

void GoodsShowItem::ShowContextMenu(const QPoint &pos){

    if(currentCount == 0){
        QMenu contextMenu(tr("Context menu"), this);

        QAction edit("Редагувати", this);

        connect(&edit, &QAction::triggered, this, &GoodsShowItem::startEdit);
        contextMenu.addAction(&edit);
        QAction dell("Видалити", this);
        connect(&dell, &QAction::triggered, this, &GoodsShowItem::startDell);
        contextMenu.addAction(&dell);

        contextMenu.exec(mapToGlobal(pos));
    }

}

void GoodsShowItem::startDell(){
    emit dell(goods->ID);
    this->hide();

}
void GoodsShowItem::startEdit(){
    emit edit(goods);
}





GoodsShowItem::~GoodsShowItem()
{
    delete ui;
}
