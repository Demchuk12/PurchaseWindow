#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include<QDateTime>
#include <QSqlError>
#include <QtSql>
const QString TABLE_ID = "ID";

const QString TABLE_GOODS = "Goods";
const QString TABLE_GOODS_NAME = "name";
const QString TABLE_GOODS_WEIGHT = "weight";
const QString TABLE_GOODS_PRICE = "price";
const QString TABLE_GOODS_DESCRIPTION = "description";
const QString TABLE_GOODS_PHOTO = "photo";
const QString TABLE_GOODS_KIND = "kind";

const QString TABLE_KIND = "kinds";
const QString TABLE_KIND_NAME = "name";

const QString TABLE_ORDER = "order";
const QString TABLE_ORDER_ID = "order_ID";
const QString TABLE_ORDER_DATE = "date";
const QString TABLE_ORDER_GOODS = "goods";
static class Database
{






void check(QSqlQuery* q);



    QSqlDatabase db;
public:
    Database();
    void init();
    const QSqlDatabase* getDB() const;


    QSqlQuery* getGoots(QString WHERE = "1");
    QSqlQuery* getOrder(QString WHERE = "1");
    QSqlQuery* getKinds(QString WHERE = "1");
    QSqlQuery* getQuery(QString PRE, QString SELECT, QString TABLE, QString WHERE, QString ORDER_BY);

    QSqlQuery* exec(QString query);



    void addGoods(QString name, int weight, float price, QString description, QString photo, int kind);
    void addOrder(int order_ID, QList<int> goods);
    void addKinds(QString name);


    void updateKinds(int ID, QString name);
    void updateGoods(int ID, QString name, int weight, float price, QString description, QString photo, int kind);















} database;

#endif // DATABASE_H
