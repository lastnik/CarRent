#include "rentallistinfomsg.h"
#include <QJsonArray>
#include <QJsonDocument>
QJsonObject RentalListInfoMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
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

IMsg* toRentalListInfoMsgStruct(QJsonDocument doc)
{
    RentalListInfoMsg* msg = new RentalListInfoMsg();
    msg->msgName = "RentalListInfoMsg";
    auto content = doc.object().value("RentalListInfoMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->from   = content.toObject().value("From").toString();
    msg->to   = content.toObject().value("To").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject RentalListInfoReq::toJsonObject()
{
    QJsonArray arr;
    for(auto& i : infoList)
    {
        arr.push_back(i->toJsonObject());
    }
    QJsonObject obj
    {
        {"Login",     login},
        {"InfoList",  arr}
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

IReq* toRentalListInfoReqStruct(QJsonDocument doc)
{
    RentalListInfoReq* req = new RentalListInfoReq();
    req->reqName = "RentalListInfoReq";
    auto content = doc.object().value("RentalListInfoReq");
    req->login   = content.toObject().value("Login").toString();
    auto arr = content.toObject().value("InfoList").toArray();
    req->infoList.resize(arr.size());
    for(size_t i = 0; i < arr.size(); i++)
    {
        QJsonDocument doc(arr[i].toObject());
        auto* item = toRentalInfoReqStruct(doc);
        req->infoList[i] = reinterpret_cast<RentalInfoReq*>(item);
    }
    return req;
}
