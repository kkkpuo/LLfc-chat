#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <memory>
#include "singleton.h"
#include "global.h"

class HttpMgr : public QObject, public Singleton<HttpMgr>,
        public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    // 发送 http 请求
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private:
    friend class Singleton<HttpMgr>;
    HttpMgr();

    QNetworkAccessManager _manager;

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    // http 请求完成信号
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    // 注册模块专用信号
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
