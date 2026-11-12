#include "httpmgr.h"
#include <QDebug>

HttpMgr::~HttpMgr()
{
}

HttpMgr::HttpMgr()
{
    // 连接 http 请求完成信号
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    // 序列化成 json 字符串
    QByteArray data = QJsonDocument(json).toJson();

    // 构造 http 请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,
                      QByteArray::number(data.length()));

    // 延长生命周期，保证回调执行期间对象存在
    auto self = shared_from_this();
    QNetworkReply *reply = _manager.post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod]() {
        // 处理错误情况
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            // 发送信号通知完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        QString res = reply->readAll();

        // 发送信号通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    // 收到注册模块的响应
    if (mod == Modules::REGISTERMOD) {
        // 发送注册模块响应信号
        emit sig_reg_mod_finish(id, res, err);
    }
}
