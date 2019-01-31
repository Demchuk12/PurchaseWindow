#ifndef GOODS_H
#define GOODS_H
#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <database.h>

struct Goods{
    QString name;
    int weight;
    float price;
    int ID;

    Goods(QString _name, int _ID, int _weight, float _price);

    QPair<QByteArray, QString> getRest();

};

#endif // GOODS_H
