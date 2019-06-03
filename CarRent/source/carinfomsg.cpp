#include "carinfomsg.h"
#include <QJsonArray>
QJsonObject CarInfoMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
        {"CarName",    carName}
    };
    QJsonObject total
    {
        {
            msgName, obj
        }
    };
    transmiterName = login;
    return total;
}

IMsg* toCarInfoMsgStruct(QJsonDocument doc)
{
    CarInfoMsg* msg = new CarInfoMsg();
    msg->msgName = "CarInfoMsg";
    auto content = doc.object().value("CarInfoMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->carName   = content.toObject().value("CarName").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject CarInfoReq::toJsonObject()
{
    return QJsonObject();
}

IReq* toCarInfoReqStruct(QJsonDocument doc)
{
    return nullptr;
}
