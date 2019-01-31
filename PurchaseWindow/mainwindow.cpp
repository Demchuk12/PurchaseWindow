#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <database.h>
#include <QtWidgets>
#include <kindmodel.h>
#include <QSizePolicy>
#include <goods.h>
#include <goodsshowitem.h>
#include <Editor/editormainwindow.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addToOrder, &QPushButton::clicked, this, &MainWindow::addGoods);
    connect(ui->PickUp, &QPushButton::clicked, this, &MainWindow::OrderDone);
    connect(ui->OpenEditor, &QPushButton::clicked, this, &MainWindow::OpenEditor);

    ui->Image->setAutoFillBackground(true);
    ui->Image->setAlignment(Qt::AlignCenter);
    QSqlQuery* kinds = database.getKinds();

    if(kinds->first()){
        do{
            QTableView* table = new QTableView(this);
            KindModel* model  =new KindModel(kinds->value(TABLE_ID).toInt());
            QStandardItemModel* header_model = new QStandardItemModel();
            header_model->setHorizontalHeaderLabels(headers);
            table->horizontalHeader()->setStretchLastSection(true);




            table->setModel(model);
            table->horizontalHeader()->setModel(header_model);
            table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Stretch  );
            table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeMode::ResizeToContents  );
            table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeMode::Custom );
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

    int w = ui->Image->width();
    int h = ui->Image->height();
    ui->Image->setPixmap(photo->scaled(w,h,Qt::KeepAspectRatio));


}


void MainWindow::OrderDone(){
    QList<QPair<int, int>> list;
    for(auto i: Order)
        list.append(QPair<int, int>(i.first->ID, i.second));
    database.addOrder(list);


}


void MainWindow::resizeEvent(QResizeEvent*){
    if(currentGoods== nullptr)return;
    auto rest = currentGoods->getRest();
    QPixmap* photo = new QPixmap();
    photo->loadFromData(rest.first);
    ui->Image->setAutoFillBackground(true);

    int w = ui->Image->width();
    int h = ui->Image->height();
    ui->Image->setPixmap(photo->scaled(w,h, Qt::KeepAspectRatio));

}

void MainWindow::addGoods(){
    if(currentGoods == nullptr) return;

    static int  counter = 0;
    Order.append(QPair<Goods*, int>(currentGoods,ui->GoodsCounter->value()));
    GoodsShowItem* g = new GoodsShowItem(currentGoods, ui->GoodsCounter->value(), counter);
    connect(g, &GoodsShowItem::mousePressEvent, this, &MainWindow::GoodsDellete);
    ui->areaOrder->layout()->addWidget(g);
    currentSum += currentGoods->price*ui->GoodsCounter->value();
    ui->SumOrder->setText(QString().number(currentSum));
    ui->GoodsCounter->setValue(1);
    counter++;

}
void MainWindow::GoodsDellete(QMouseEvent *event) {
    if(event->button() == Qt::RightButton){
        GoodsShowItem *goods = dynamic_cast<GoodsShowItem*>( sender());
        Order.removeAt(goods->Plase);
        goods->hide();
        currentSum -= goods->currentPrice;
        ui->SumOrder->setText(QString().number(currentSum));
    }

}



void MainWindow::OpenEditor(){

    EditorMainWindow *ed = new EditorMainWindow();
    ed->show();
    this->hide();


}


MainWindow::~MainWindow()
{
    delete ui;
}
