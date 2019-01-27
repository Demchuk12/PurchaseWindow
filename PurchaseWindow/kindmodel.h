#ifndef KINDMODEL_H
#define KINDMODEL_H
#include <QAbstractTableModel>
#include <database.h>
#include <goods.h>
class KindModel:public QAbstractTableModel
{
public :

private:
    int row_Count = 0;
    int column_Count = 3;



    QList<Goods*> table;
    bool Empty = false;
public:
    Goods* getGoods(int n){

        return  table.at(n);
    }

    bool isEmpty(){return Empty; }
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    KindModel(int kindID);
};

#endif // KINDMODEL_H
