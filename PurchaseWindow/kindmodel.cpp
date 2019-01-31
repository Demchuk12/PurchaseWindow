#include "kindmodel.h"
#include <QSqlQuery>
#include <goods.h>


KindModel::KindModel(int kindID)
{
    QSqlQuery* goods =  database.getGoots(TABLE_GOODS_KIND + " = "+QString().number(kindID));

    row_Count = 0;
    if(goods->first()){
        do{
            row_Count++;

            QString name = goods->value(TABLE_GOODS_NAME).toString();
            int ID = goods->value(TABLE_ID).toInt();
            int weight = goods->value(TABLE_GOODS_WEIGHT).toInt();
            float price = goods->value(TABLE_GOODS_PRICE).toFloat();
            table.append(new Goods(name, ID, weight, price));


        }while(goods->next());

    }else Empty = true;




}


int KindModel::columnCount(const QModelIndex&) const {
    return column_Count;
}
int KindModel::rowCount(const QModelIndex&) const {
    return row_Count;
}

QVariant KindModel::data(const QModelIndex &index, int role) const{

    if(role == Qt::DisplayRole){

        if(index.column() == 0)
            return QVariant(table.at(index.row())->name);
        else if(index.column() == 1)
            return QVariant(QString().number(table.at(index.row())->weight)+ " гр");
        else if(index.column() == 2)
            return QVariant(QString().number(table.at(index.row())->price)+ " грн");
    }
    return QVariant();
}
