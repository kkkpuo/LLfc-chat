#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <QObject>
#include "singleton.h"
class HttpMgr: public QObject,Singleton<HttpMgr>
{
    Q_OBJECT
public:
    HttpMgr();
};

#endif // HTTPMGR_H
