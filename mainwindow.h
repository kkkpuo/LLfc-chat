#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "regist.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SlotSwitchReg();
private:
    Ui::MainWindow *ui;
    LoginDialog *_login_dlg;
    regist *_regist_dlg;
};
#endif // MAINWINDOW_H
