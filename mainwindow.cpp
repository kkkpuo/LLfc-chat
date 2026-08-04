#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QQ");
    _login_dlg = new LoginDialog(this);
    setCentralWidget(_login_dlg);
    _login_dlg->show();
    connect(_login_dlg, &LoginDialog::switchRegist,
            this, &MainWindow::SlotSwitchReg);
    _regist_dlg = new regist(this);
    //把对话框嵌在mainwindow中
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _regist_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_regist_dlg);
    _login_dlg->hide();
    _regist_dlg->show();
}
