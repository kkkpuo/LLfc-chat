#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <QString>
#include <functional>
#include "QStyle"

extern std::function<void(QWidget *)> repolish;

// 请求 id，用于区分不同 http 请求的响应
enum ReqId {
    ID_GET_VARIFY_CODE = 1001, // 获取验证码
    ID_REG_USER = 1002,        // 注册用户
};

// 模块号，用于区分请求来自哪个模块
enum Modules {
    REGISTERMOD = 0,
};

// 错误码
enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON = 1,
    ERR_NETWORK = 2,
};

// 网关地址前缀
extern QString gate_url_prefix;

#endif // GLOBAL_H
