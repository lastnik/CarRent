#include "rentalrespondmsg.h"
#include <QJsonArray>
QJsonObject RentalRespondMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",        login},
        {"CarName",      carName},
        {"CarOwner",     carOwner},
        {"RentalUser",   rentalUser},
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

IMsg* toRentalRespondMsgStruct(QJsonDocument doc)
{
    RentalRespondMsg* msg = new RentalRespondMsg();
    msg->msgName = "RentalRespondMsg";
    auto content = doc.object().value("RentalRespondMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->carName   = content.toObject().value("CarName").toString();
    msg->carOwner   = content.toObject().value("CarOwner").toString();
    msg->rentalUser   = content.toObject().value("RentalUser").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject RentalRespondReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
        {"CarName",    carName},
        {"CarOwner",   carOwner},
        {"RentalUser",   rentalUser},
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

IReq* toRentalRespondReqStruct(QJsonDocument doc)
{
    RentalRespondReq* req = new RentalRespondReq();
    req->reqName = "RentalRespondReq";
    auto content = doc.object().value("RentalRespondReq");
    req->login   = content.toObject().value("Login").toString();
    req->carName   = content.toObject().value("CarName").toString();
    req->carOwner   = content.toObject().value("CarOwner").toString();
    req->rentalUser   = content.toObject().value("RentalUser").toString();
    req->receiverName = req->login;
    return req;
}

