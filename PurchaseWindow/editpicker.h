#ifndef EDITPICKER_H
#define EDITPICKER_H

#include <QMainWindow>

namespace Ui {
class EditPicker;
}

class EditPicker : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditPicker(QWidget *parent = nullptr);
    ~EditPicker();

private:
    Ui::EditPicker *ui;
};

#endif // EDITPICKER_H
