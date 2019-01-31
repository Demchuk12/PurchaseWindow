#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <database.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  database.init();/*
  QDialog* dial = new  QDialog();
  dial->show();

  QMessageBox::warning(nullptr, "eeee", QString().number(  dial->result()));

*/
//    database.addGoods("testName2", 3, 4.2f, "testDes", "C:/Users/user/Desktop/testPhoto.png", 1);
      MainWindow w;
    w.show();


    return a.exec();
}
