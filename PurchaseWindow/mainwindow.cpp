#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <database.h>
#include <QtWidgets>
#include <kindmodel.h>
#include <goods.h>
#include <goodsshowitem.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addToOrder, &QPushButton::clicked, this, &MainWindow::addGoods);
    ui->Image->setAutoFillBackground(true);
    QSqlQuery* kinds = database.getKinds();

    if(kinds->first()){
        do{
            QTableView* table = new QTableView(this);
            KindModel* model  =new KindModel(kinds->value(TABLE_ID).toInt());

            model->setHeaderData(0, Qt::Horizontal, tr("Назва"));
            model->setHeaderData(1, Qt::Horizontal, tr("Вага"), Qt::DisplayRole);
            model->setHeaderData(2, Qt::Horizontal, tr("Ціна"), Qt::DisplayRole);
            table->resizeColumnsToContents();

            table->setModel(model);
            connect(table, &QTableView::doubleClicked, this, &MainWindow::GoodsChanged);
            ui->tabWidget->addTab(table, kinds->value(TABLE_KIND_NAME).toString());
        }while(kinds->next());
    }
}
void MainWindow::GoodsChanged(const QModelIndex &index){
    currentGoods = (dynamic_cast<KindModel*>(
                        (dynamic_cast<QTableView*>(sender()))->model()))->getGoods(index.row());
    auto rest = currentGoods->getRest();
    ui->Name->setText(currentGoods->name);
    ui->Description->setText(rest.second);
    QPixmap* photo = new QPixmap();
    photo->loadFromData(rest.first);
    ui->Image->setAutoFillBackground(true);
    ui->Image->setPixmap(photo->scaled(400, 400));

}

void MainWindow::addGoods(){
   if(currentGoods == nullptr) return;
   Order.append(QPair<Goods*, int>(currentGoods,ui->GoodsCounter->value()));
   ui->areaOrder->layout()->addWidget(new GoodsShowItem(currentGoods, ui->GoodsCounter->value()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
