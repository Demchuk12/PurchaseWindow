#include "mainwindow.h"
#include <QApplication>
#include <database.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  database.init();
    MainWindow w;

//    database.addGoods("testName2", 3, 4.2f, "testDes", "C:/Users/user/Desktop/testPhoto.png", 1);
    w.show();


    return a.exec();
}
