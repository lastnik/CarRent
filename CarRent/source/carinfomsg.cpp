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
    QJsonArray arr;
    for(auto i : documents)
    {
        QJsonObject obj
        {
            {"DocumentName", i.first},
            {"DocumentFileName", i.second}
        };
        arr.push_back(obj);
    }
    QJsonObject obj
    {
        {"Login",     login},
        {"CarName",   carName},
        {"CarBrend",  carBrend},
        {"CarModel",  carModel},
        {"CarColor",  carColor},
        {"CarNumber", carNumber},
        {"Year",      year},
        {"isCar",     isCar},
        {"CarOwner",  carOwner},
        {"CarState",  carState},
        {"Documents", arr},
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

IReq* toCarInfoReqStruct(QJsonDocument doc)
{
    CarInfoReq* req = new CarInfoReq();
    req->reqName = "CarInfoReq";
    auto content = doc.object().value("CarInfoReq");
    req->login   = content.toObject().value("Login").toString();
    auto arr     = content.toObject().value("Documents").toArray();
    req->receiverName = req->login;
    for(auto i : arr)
    {
        req->documents.push_back(std::make_pair( i.toObject().value("DocumentName").toString()
                                               , i.toObject().value("DocumentFileName").toString()));
    }
    req->carBrend   = content.toObject().value("CarBrend").toString();
    req->carModel   = content.toObject().value("CarModel").toString();
    req->carColor   = content.toObject().value("CarColor").toString();
    req->carNumber  = content.toObject().value("CarNumber").toString();
    req->carName    = content.toObject().value("CarName").toString();
    req->year       = content.toObject().value("Year").toInt();
    req->isCar      = content.toObject().value("isCar").toBool();
    req->carOwner   = content.toObject().value("CarOwner").toString();
    req->carState   = content.toObject().value("CarState").toString();
    return req;
}
