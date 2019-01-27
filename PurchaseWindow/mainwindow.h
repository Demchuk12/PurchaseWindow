#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <goods.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Goods* currentGoods= nullptr;
    QList<QPair<Goods*, int>> Order;
    float currentSum;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void GoodsChanged(const QModelIndex &index);
    void addGoods();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
