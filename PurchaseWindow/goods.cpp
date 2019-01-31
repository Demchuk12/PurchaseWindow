#include "goods.h"

Goods::Goods(QString _name, int _ID, int _weight, float _price):name(_name),  weight(_weight), price(_price), ID(_ID){
}
QPair<QByteArray, QString> Goods::getRest(){
    QSqlQuery* query = database.getGoots(TABLE_ID +  " = " + QString().number(ID));
    query->first();
    return   QPair<QByteArray, QString>(query->value(TABLE_GOODS_PHOTO).toByteArray(), query->value(TABLE_GOODS_DESCRIPTION).toString());

}
