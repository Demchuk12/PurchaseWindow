#ifndef EDITORMAINWINDOW_H
#define EDITORMAINWINDOW_H

#include <QMainWindow>
#include <goods.h>
#include <QtWidgets>
#include <kindmodel.h>
namespace Ui {
class EditorMainWindow;
}

class EditorMainWindow : public QMainWindow
{
    Q_OBJECT
    bool modeEditing;
    QList<Goods*> getGoods(int Kind_ID);
    Goods* currerntGoods = nullptr;
    void reload();
public:
    explicit EditorMainWindow(QWidget *parent = nullptr);
    ~EditorMainWindow();

private slots:
    void editGoods(Goods* goods);
    void dellGoods(int ID);
    void addGoods();
    void addKind();
    void endInputing();
    void ChoosePhoto();

private:
    Ui::EditorMainWindow *ui;
};

#endif // EDITORMAINWINDOW_H
