#include "carinfomsg.h"
#include <QJsonArray>
QJsonObject CarInfoMsg::toJsonObject()
{
    return QJsonObject();
}

IMsg* toCarInfoMsgStruct(QJsonDocument doc)
{
    return nullptr;
}

QJsonObject CarInfoReq::toJsonObject()
{
    return QJsonObject();
}

IReq* toCarInfoReqStruct(QJsonDocument doc)
{
    return nullptr;
}
