#include "editpicker.h"
#include "ui_editpicker.h"

EditPicker::EditPicker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditPicker)
{
    ui->setupUi(this);

}

EditPicker::~EditPicker()
{
    delete ui;
}
