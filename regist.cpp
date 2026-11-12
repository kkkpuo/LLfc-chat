#include "regist.h"
#include "ui_regist.h"
#include "global.h"
#include "httpmgr.h"
#include <QDebug>
#include <QJsonDocument>

regist::regist(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::regist)
{
    ui->setupUi(this);

    ui->error_tip->setProperty("state","normal");
    repolish(ui->error_tip);

    // 连接 http 管理类的注册模块信号，注意 GetInstance 返回的是 shared_ptr
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
            this, &regist::slot_reg_mod_finish);

    // 初始化请求 id 对应的处理函数
    initHttpHandlers();
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

void regist::initHttpHandlers()
{
    // 注册获取验证码回包的处理逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject &jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"), true);
        qDebug()<< "email is " << email ;
    });
}

void regist::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    // json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }

    // json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    // 根据 id 调用对应的逻辑，先判断是否注册过处理函数
    if(!_handlers.contains(id)){
        showTip(tr("未知的请求类型"),false);
        return;
    }
    _handlers[id](jsonObj);

    return;
}
