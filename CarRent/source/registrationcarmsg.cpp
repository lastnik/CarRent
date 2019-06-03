#include "registrationcarmsg.h"
#include <QJsonArray>
#include <QFile>

QJsonObject RegistrationCarMsg::toJsonObject()
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
        {"CarBrend",  carBrend},
        {"CarModel",  carModel},
        {"CarColor",  carColor},
        {"CarNumber", carNumber},
        {"Year",      year},
        {"Documents", arr},
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

IMsg* toRegistrationCarMsgStruct(QJsonDocument doc)
{
    RegistrationCarMsg* msg = new RegistrationCarMsg();
    msg->msgName = "RegistrationCarMsg";
    auto content = doc.object().value("RegistrationCarMsg");
    msg->login   = content.toObject().value("Login").toString();
    auto arr     = content.toObject().value("Documents").toArray();
    msg->transmiterName = msg->login;
    for(auto i : arr)
    {
        msg->documents.push_back(std::make_pair( i.toObject().value("DocumentName").toString()
                                               , i.toObject().value("DocumentFileName").toString()));
    }
    msg->carBrend  = content.toObject().value("CarBrend").toString();
    msg->carModel  = content.toObject().value("CarModel").toString();
    msg->carColor  = content.toObject().value("CarColor").toString();
    msg->carNumber = content.toObject().value("CarNumber").toString();
    msg->year      = content.toObject().value("Year").toInt();
    return msg;
}

QJsonObject RegistrationCarReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",     login},
        {"CarName",   carName},
        {"isCar",     isCar}
    };
    QJsonObject total
    {
        {
            reqName, obj
        }
    };
    return total;
}

IReq* toRegistrationCarReqStruct(QJsonDocument doc)
{
    RegistrationCarReq* req = new RegistrationCarReq();
    req->reqName = "RegistrationCarReq";
    auto content = doc.object().value("RegistrationCarReq");
    req->login   = content.toObject().value("Login").toString();
    req->carName = content.toObject().value("CarName").toString();
    req->isCar   = content.toObject().value("isCar").toBool();
    req->receiverName = req->login;
    return req;
}
