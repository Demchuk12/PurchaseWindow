#include "editormainwindow.h"
#include "ui_editormainwindow.h"
#include <goods.h>
#include <goodsshowitem.h>
#include <QValidator>
EditorMainWindow::EditorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorMainWindow)
{

    ui->setupUi(this);
    setAutoFillBackground(true);
    ui->InputFormWidget->hide();
    connect(ui->addPhotoButton, &QPushButton::clicked, this, &EditorMainWindow::ChoosePhoto);
    connect(ui->AddAction->actions()[1], &QAction::triggered, this, &EditorMainWindow::addKind);
    connect(ui->AddAction->actions()[0], &QAction::triggered, this, &EditorMainWindow::addGoods);



    connect(ui->okButton, &QPushButton::clicked, this, &EditorMainWindow::endInputing);
    reload();

}

void EditorMainWindow::reload(){
    ui->PickTabWidget->clear();
    QSqlQuery* kinds = database.getKinds();
    int row = -1;
    if(kinds->first()){
        do{
            ui->comboBoxKind->addItem(kinds->value(TABLE_KIND_NAME).toString(), kinds->value(TABLE_ID).toInt());
            QWidget* widget = new QWidget();

            QGridLayout* grid = new QGridLayout(widget);
            auto list = getGoods(kinds->value(TABLE_ID).toInt());
            for(int i = 0 ; i < list.length(); i++){
                if(i%3 == 0) row++;
                GoodsShowItem* item =new GoodsShowItem(list[i], 0, 0);
                connect(item, &GoodsShowItem::edit, this, &EditorMainWindow::editGoods);
                connect(item, &GoodsShowItem::dell, this, &EditorMainWindow::dellGoods);
                grid->addWidget(item, row, i%3, Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft);
            }
            row = -1;

            widget->setLayout(grid);
            ui->PickTabWidget->addTab(widget, kinds->value(TABLE_KIND_NAME).toString());


        }while(kinds->next());
    }

}


QList<Goods*> EditorMainWindow::getGoods(int Kind_ID){
    QSqlQuery* goods =  database.getGoots(TABLE_GOODS_KIND + " = "+QString().number(Kind_ID));
    QList<Goods*> res;
    if(goods->first()){
        do{


            QString name = goods->value(TABLE_GOODS_NAME).toString();
            int ID = goods->value(TABLE_ID).toInt();
            int weight = goods->value(TABLE_GOODS_WEIGHT).toInt();
            float price = goods->value(TABLE_GOODS_PRICE).toFloat();
            res.append(new Goods(name, ID, weight, price));


        }while(goods->next());

    }
    return res;
}

void EditorMainWindow::editGoods(Goods* goods){
    ui->PickTabWidget->hide();
    ui->InputFormWidget->show();
    auto rest = goods->getRest();
    currerntGoods = goods;
    ui->nameLineEdit->setText(goods->name);
    ui->priceSpinBox->setValue(goods->price);
    ui->weightSpinBox->setValue(goods->weight);
    ui->descriptionTextEdit->setText(rest.second);


}
void EditorMainWindow::dellGoods(int ID){
    database.exec("DELETE FROM "+ TABLE_GOODS+ " WHERE "+TABLE_ID+ " = "+QString().number(ID));
}

void EditorMainWindow::endInputing(){
    if(ui->nameLineEdit->text().isEmpty()||
            ui->priceSpinBox->value() == 0.0f||
            ui->weightSpinBox->value()== 0) return;
    if(currerntGoods == nullptr){
        QMessageBox::warning(nullptr, "sdcs",QString().number(ui->priceSpinBox->value()));
        database.addGoods(ui->nameLineEdit->text(),
                          ui->weightSpinBox->value(),
                          ui->priceSpinBox->value(),
                          ui->descriptionTextEdit->toPlainText(),
                          ui->photoLineEdit->text(),
                          ui->comboBoxKind->currentData().toInt());
    }else{
        database.updateGoods(currerntGoods->ID,
                             ui->nameLineEdit->text(),
                             ui->weightSpinBox->value(),
                             ui->priceSpinBox->value(),
                             ui->descriptionTextEdit->toPlainText(),
                             ui->photoLineEdit->text(),
                             ui->comboBoxKind->currentData().toInt());
        currerntGoods = nullptr;

    }
    ui->InputFormWidget->hide();
    ui->PickTabWidget->show();
    reload();


}

void EditorMainWindow::ChoosePhoto(){
    ui->photoLineEdit->setText(QFileDialog::getOpenFileName());
}


void EditorMainWindow::addGoods(){

    modeEditing = true;
    ui->PickTabWidget->hide();
    ui->InputFormWidget->show();


}
void EditorMainWindow::addKind(){
    QInputDialog* Input = new QInputDialog();
    Input->setLabelText("Введіть імя");
    Input->show();
    connect(Input, &QInputDialog::textValueSelected, [&](const QString &text){
        database.addKinds(text);
        this->reload();
    });
}


EditorMainWindow::~EditorMainWindow()
{
    delete ui;
}
