#include "accessmsg.h"
#include <QJsonArray>
QJsonObject AccessMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",    login},
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

IMsg* toAccessMsgStruct(QJsonDocument doc)
{
    AccessMsg* msg = new AccessMsg();
    msg->msgName = "AccessMsg";
    auto content = doc.object().value("AccessMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject AccessReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",    login},
        {"isPerson", isPerson},
        {"hasCars",  hasCars}
    };
    QJsonArray person;
    for(auto i : documents)
    {
        QJsonObject value
        {
            {"DocumentsName",    i.first},
            {"DocumentsConfirm", i.second}
        };
        person.push_back(value);
    }
    obj.insert("PersonalDocuments", person);
    QJsonArray cars;
    for(auto i : carsNames)
    {
        cars.push_back(i);
    }
    obj.insert("CarNames", cars);
    QJsonObject total
    {
        {
            reqName, obj
        }
    };
    return total;
}

IReq* toAccessReqStruct(QJsonDocument doc)
{
    AccessReq* req = new AccessReq();
    req->reqName = "AccessReq";
    auto content = doc.object().value("AccessReq");
    req->login    = content.toObject().value("Login").toString();
    req->isPerson = content.toObject().value("isPerson").toBool();
    req->hasCars  = content.toObject().value("hasCars").toBool();
    auto person   = content.toObject().value("PersonalDocuments").toArray();
    for(auto i : person)
    {
        req->documents.push_back(std::make_pair( i.toObject().value("DocumentsName").toString()
                                               , i.toObject().value("DocumentsConfirm").toBool()));
    }
    auto cars     = content.toObject().value("CarNames").toArray();
    for(auto i : cars)
    {
        req->carsNames.push_back(i.toString());
    }
    return req;
}
