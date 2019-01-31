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
    QStringList headers = {"Назва","Вага","Ціна"};
    Q_OBJECT
    Goods* currentGoods= nullptr;
    QList<QPair<Goods*, int>> Order;
    float currentSum;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void resizeEvent(QResizeEvent* ) override;


    void GoodsChanged(const QModelIndex &index);
    void addGoods();
    void GoodsDellete(QMouseEvent *event);
    void OrderDone();
    void OpenEditor();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
