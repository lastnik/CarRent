#include <QJsonArray>
#include <QFile>
#include "registrationmsg.h"
QJsonObject RegistrationMsg::toJsonObject()
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
        {"Login",    login},
        {"Documents",  arr},
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

IMsg* toRegistrationMsgStruct(QJsonDocument doc)
{
    RegistrationMsg* msg = new RegistrationMsg();
    msg->msgName = "RegistrationMsg";
    auto content = doc.object().value("RegistrationMsg");
    msg->login   = content.toObject().value("Login").toString();
    auto arr     = content.toObject().value("Documents").toArray();
    msg->transmiterName = msg->login;
    for(auto i : arr)
    {
        msg->documents.push_back(std::make_pair( i.toObject().value("DocumentName").toString()
                                               , i.toObject().value("DocumentFileName").toString()));
    }
    return msg;
}

QJsonObject RegistrationReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",     login},
        {"isPerson",  isPerson},
    };
    QJsonObject total
    {
        {
            reqName, obj
        }
    };
    return total;
}

IReq* toRegistrationReqStruct(QJsonDocument doc)
{
    RegistrationReq* req = new RegistrationReq();
    req->reqName = "RegistrationReq";
    auto content = doc.object().value("RegistrationReq");
    req->login   = content.toObject().value("Login").toString();
    req->isPerson = content.toObject().value("isPerson").toBool();
    req->receiverName = req->login;
    return req;
}
