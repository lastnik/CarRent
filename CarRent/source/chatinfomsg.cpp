#include "chatinfomsg.h"
#include <QJsonArray>
QJsonObject ChatInfoMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
        {"CarName",    carName},
        {"CarOwner",   carOwner},
        {"UserName",   userName},
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

IMsg* toChatInfoMsgStruct(QJsonDocument doc)
{
    ChatInfoMsg* msg = new ChatInfoMsg();
    msg->msgName = "ChatInfoMsg";
    auto content = doc.object().value("ChatInfoMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->carName   = content.toObject().value("CarName").toString();
    msg->carOwner   = content.toObject().value("CarOwner").toString();
    msg->userName   = content.toObject().value("UserName").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject ChatInfoReq::toJsonObject()
{
    QJsonArray arr;
    for(auto i : chat)
    {
        QJsonObject obj
        {
            {"Name", i.first},
            {"Message", i.second}
        };
        arr.push_back(obj);
    }
    QJsonObject obj
    {
        {"Login",     login},
        {"CarName",   carName},
        {"CarOwner",  carOwner},
        {"UserName",  userName},
        {"Chat", arr},
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

IReq* toChatInfoReqStruct(QJsonDocument doc)
{
    ChatInfoReq* req = new ChatInfoReq();
    req->reqName = "ChatInfoReq";
    auto content = doc.object().value("ChatInfoReq");
    req->login   = content.toObject().value("Login").toString();
    auto arr     = content.toObject().value("Chat").toArray();
    req->receiverName = req->login;
    for(auto i : arr)
    {
        req->chat.push_back(std::make_pair( i.toObject().value("Name").toString()
                                          , i.toObject().value("Message").toString()));
    }
    req->carName    = content.toObject().value("CarName").toString();
    req->carOwner   = content.toObject().value("CarOwner").toString();
    req->userName   = content.toObject().value("UserName").toString();
    return req;
}
