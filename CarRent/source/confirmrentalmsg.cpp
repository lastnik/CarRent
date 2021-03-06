#include "confirmrentalmsg.h"
#include <QJsonArray>
QJsonObject ConfirmRentalMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
        {"CarName",    carName},
        {"Cost",       cost},
        {"From",       from},
        {"To",         to}
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

IMsg* toConfirmRentalMsgStruct(QJsonDocument doc)
{
    ConfirmRentalMsg* msg = new ConfirmRentalMsg();
    msg->msgName = "ConfirmRentalMsg";
    auto content = doc.object().value("ConfirmRentalMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->carName   = content.toObject().value("CarName").toString();
    msg->cost   = content.toObject().value("Cost").toDouble();
    msg->from   = content.toObject().value("From").toString();
    msg->to   = content.toObject().value("To").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject ConfirmRentalReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",     login},
        {"CarName",   carName},
        {"Result",    result},
    };
    QJsonObject total
    {
        {
            reqName, obj
        }
    };
    receiverName = login;
    return total;
}

IReq* toConfirmRentalReqStruct(QJsonDocument doc)
{
    ConfirmRentalReq* req = new ConfirmRentalReq();
    req->reqName = "ConfirmRentalReq";
    auto content = doc.object().value("ConfirmRentalReq");
    req->login   = content.toObject().value("Login").toString();
    req->receiverName = req->login;
    req->carName      = content.toObject().value("CarName").toString();
    req->result       = content.toObject().value("Result").toBool();
    return req;
}
