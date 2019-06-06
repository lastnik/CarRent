#include "rentalinfomsg.h"
QJsonObject RentalInfoMsg::toJsonObject()
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

IMsg* toRentalInfoMsgStruct(QJsonDocument doc)
{
    RentalInfoMsg* msg = new RentalInfoMsg();
    msg->msgName = "RentalInfoMsg";
    auto content = doc.object().value("RentalInfoMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->carName   = content.toObject().value("CarName").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject RentalInfoReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",     login},
        {"CarName",   carName},
        {"RentUser",  rentUser},
        {"From",      from},
        {"To",        to},
        {"Cost",      cost}
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

IReq* toRentalInfoReqStruct(QJsonDocument doc)
{
    RentalInfoReq* req = new RentalInfoReq();
    req->reqName = "RentalInfoReq";
    auto content = doc.object().value("RentalInfoReq");
    req->login   = content.toObject().value("Login").toString();
    req->carName = content.toObject().value("CarName").toString();
    req->from    = content.toObject().value("From").toString();
    req->to      = content.toObject().value("To").toString();
    req->cost    = content.toObject().value("Cost").toDouble();
    req->rentUser = content.toObject().value("RentUser").toString();
    return req;
}
