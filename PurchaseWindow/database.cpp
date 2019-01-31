#include "database.h"

Database::Database()
{

}

const QSqlDatabase* Database::getDB() const{
    return &db;
}
void Database::check(QSqlQuery* q){
    if(!q->exec()){
        QMessageBox::warning(nullptr, "Error", q->lastError().text());
    }

}



void Database::init(){
   db =  QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("DataBase.db");
   if(!db.open()) {
       QMessageBox::warning(nullptr, "Error open", db.lastError().text());
       return;
   }

}


QSqlQuery* Database::getGoots(QString WHERE){
    QSqlQuery* query = new QSqlQuery(db);
    query->exec("SELECT * FROM " + TABLE_GOODS + " WHERE "+ WHERE);
    return query;

}
QSqlQuery* Database::getKinds(QString WHERE ){
    QSqlQuery* query = new QSqlQuery(db);
    query->exec("SELECT * FROM " + TABLE_KIND + " WHERE "+ WHERE);
    return query;

}QSqlQuery* Database::getOrder(QString WHERE ){
    QSqlQuery* query = new QSqlQuery(db);
    query->exec("SELECT * FROM " + TABLE_ORDER + " WHERE "+ WHERE);
    return query;

}
QSqlQuery* Database::getQuery(QString PRE, QString SELECT, QString TABLE, QString WHERE, QString ORDER_BY){
    QSqlQuery* query = new QSqlQuery(db);
    query->exec(PRE + " SELECT " +SELECT +" FROM " + TABLE + " WHERE "+ WHERE + " ORDER BY "+ ORDER_BY);
    return query;

}
QSqlQuery* Database::exec(QString query){
    QSqlQuery* q = new QSqlQuery(db);
    q->exec(query);
    return q;

}


void Database::addGoods(QString name, int weight, float price, QString description, QString photoPath, int kind){

    QPixmap photo(photoPath);
    QByteArray byteArr;
    QBuffer buf(&byteArr);
    buf.open(QIODevice::WriteOnly);
    photo.save(&buf, "PNG");
    QMessageBox::warning(nullptr, "sdofvhj dc", QString().number(price));
    QSqlQuery* query = new QSqlQuery(db);
    query->prepare("INSERT INTO " + TABLE_GOODS+" ( "
                  +TABLE_GOODS_NAME +", "
                  +TABLE_GOODS_WEIGHT +", "
                  +TABLE_GOODS_PRICE+", "
                  +TABLE_GOODS_DESCRIPTION+ ", "
                  +TABLE_GOODS_PHOTO +", "
                  +TABLE_GOODS_KIND  +" "
                  +" ) VALUES (:name, :weight, :price, :description, :photo, :kind)");
    query->bindValue(":name", name);
    query->bindValue(":weight", weight);
    query->bindValue(":price", price);
    query->bindValue(":description", description);
    query->bindValue(":photo", byteArr);
    query->bindValue(":kind", kind);
    if(!query->exec()){
        QMessageBox::warning(nullptr, "Error", query->lastError().text());
    }

}
void Database::addOrder(QList<QPair<int, int>> goods){
    QDateTime  dt;
    QSqlQuery* q = getOrder(" 1 ORDER BY "+TABLE_ORDER_ID + " DESC");
    QMessageBox::warning(nullptr, "1", "1");
    int ID;
    if(q->first()){
          ID = q->value(TABLE_ORDER_ID).toInt()+1;
    }else{
        ID = 0;
    }
    QString date = dt.currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    for(auto i : goods){
     QSqlQuery* query = new QSqlQuery(db);
        query->prepare("INSERT INTO " + TABLE_ORDER+" ("
                      +TABLE_ORDER_ID + ", "
                      +TABLE_ORDER_DATE + ", "
                      +TABLE_ORDER_GOODS + ", "
                      +TABLE_ORDER_COUNT + " "
                      +") VALUES (:order_id, :date, :goods, :count)");
        query->bindValue(":order_id", ID);
        query->bindValue(":date", date);
        query->bindValue(":goods", i.first);
        query->bindValue(":count", i.second);

        check(query);
    }






}
void Database::addKinds(QString name){
    QSqlQuery query(db);
    query.prepare("INSERT INTO "+ TABLE_KIND+ "(" + TABLE_KIND_NAME+") VALUES (:name)");
    query.bindValue(":name", name);
    check(&query);
}






void Database::updateKinds(int ID, QString name){
    QSqlQuery  query(db);

    query.prepare("UPDATE "+TABLE_KIND+" Set name = :name WHERE ID ="+QString().number(ID));
    query.bindValue(":name", name);
    check(&query);
}


void Database::updateGoods(int ID, QString name, int weight, float price, QString description, QString photoPath, int kind){
    if(description.isEmpty()){
        QSqlQuery  query(db);

        query.prepare("UPDATE "+TABLE_GOODS+" SET "
                      +TABLE_GOODS_NAME+" = :name, "
                      +TABLE_GOODS_WEIGHT + " = :weight, "
                      +TABLE_GOODS_PRICE + " = :price, "
                      +TABLE_GOODS_DESCRIPTION + " = :description, "
                      +TABLE_GOODS_KIND + " = :kind "+
                      " WHERE ID = "+QString().number(ID));
        query.bindValue(":name", name);
        query.bindValue(":weight", weight);
        query.bindValue(":price", price);
        query.bindValue(":description", description);
        query.bindValue(":kind", kind);
        check(&query);
        return;

    }
    QPixmap photo(photoPath);
    QByteArray byteArr;
    QBuffer buf(&byteArr);
    buf.open(QIODevice::WriteOnly);
    photo.save(&buf, "PNG");
    QSqlQuery  query(db);

    query.prepare("UPDATE "+TABLE_GOODS+" SET "
                  +TABLE_GOODS_NAME+" = :name, "
                  +TABLE_GOODS_WEIGHT + " = :weight, "
                  +TABLE_GOODS_PRICE + " = :price, "
                  +TABLE_GOODS_DESCRIPTION + " = :description, "
                  +TABLE_GOODS_PHOTO + " = :photo, "
                  +TABLE_GOODS_KIND + " = :kind "+
                  " WHERE ID = "+QString().number(ID));
    query.bindValue(":name", name);
    query.bindValue(":weight", weight);
    query.bindValue(":price", price);
    query.bindValue(":description", description);
    query.bindValue(":photo", byteArr);
    query.bindValue(":kind", kind);
    check(&query);


}




