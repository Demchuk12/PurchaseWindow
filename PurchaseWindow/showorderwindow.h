#ifndef SHOWORDERWINDOW_H
#define SHOWORDERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ShowOrderWindow;
}

class ShowOrderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowOrderWindow(QWidget *parent = nullptr);
    ~ShowOrderWindow();

private:
    Ui::ShowOrderWindow *ui;
};

#endif // SHOWORDERWINDOW_H
