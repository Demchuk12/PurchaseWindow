#include "showorderwindow.h"
#include "ui_showorderwindow.h"

ShowOrderWindow::ShowOrderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowOrderWindow)
{
    ui->setupUi(this);
}

ShowOrderWindow::~ShowOrderWindow()
{
    delete ui;
}
