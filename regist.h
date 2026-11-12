#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include <QRegularExpression>
#include <QMap>
#include <QString>
#include <QJsonObject>
#include <functional>
#include "global.h"

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();

private slots:
    void on_pushButton_Gain_clicked();
    // 注册模块 http 响应处理槽
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void showTip(QString str, bool cof);

private:
    // 初始化 http 请求的处理函数
    void initHttpHandlers();

    Ui::regist *ui;
    // 请求 id -> 处理函数，收到回包后按 id 分派
    QMap<ReqId, std::function<void(const QJsonObject &)>> _handlers;
};

#endif // REGIST_H
