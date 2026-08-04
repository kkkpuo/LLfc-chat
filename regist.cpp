#include "regist.h"
#include "ui_regist.h"
#include"global.h"
regist::regist(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::regist)
{
    ui->setupUi(this);

    ui->error_tip->setProperty("state","normal");
    repolish(ui->error_tip);
}

regist::~regist()
{
    delete ui;
}

void regist::on_pushButton_Gain_clicked()
{
    auto email = ui->lineEdit_Email->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        //发送http请求获取验证码
    }else{
        //提示邮箱不正确
        showTip(tr("邮箱地址不正确"),false);
    }
}

void regist::showTip(QString str, bool cof)
{
    if(cof)
    {
        ui->error_tip->setProperty("state","normal");
    }
    else
    {
        ui->error_tip->setProperty("state","err");
    }
    ui->error_tip->setText(str);
    repolish(ui->error_tip);
}


