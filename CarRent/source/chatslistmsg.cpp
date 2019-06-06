#include "chatslistmsg.h"
#include <QJsonArray>

QJsonObject ChatListMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
        {"CarName",    carName},
        {"CarOwner",   carOwner},
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

IMsg* toChatListMsgStruct(QJsonDocument doc)
{
    ChatListMsg* msg = new ChatListMsg();
    msg->msgName = "ChatListMsg";
    auto content = doc.object().value("ChatListMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->carName   = content.toObject().value("CarName").toString();
    msg->carOwner   = content.toObject().value("CarOwner").toString();
    msg->transmiterName = msg->login;
    return msg;
}


QJsonObject ChatListReq::toJsonObject()
{
    QJsonArray arr1;
    for(auto i : userName)
    {
        QJsonObject obj
        {
            {"Name", i}
        };
        arr1.push_back(obj);
    }
    QJsonObject obj
    {
        {"Login",     login},
        {"CarName",   carName},
        {"CarOwner",  carOwner},
        {"UserNames", arr1}
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

IReq* toChatListReqStruct(QJsonDocument doc)
{
    ChatListReq* req = new ChatListReq();
    req->reqName = "ChatListReq";
    auto content = doc.object().value("ChatListReq");
    req->login   = content.toObject().value("Login").toString();
    auto arr1     = content.toObject().value("UserNames").toArray();
    req->receiverName = req->login;
    for(auto i : arr1)
    {
        req->userName.push_back(i.toObject().value("Name").toString());
    }
    req->carName    = content.toObject().value("CarName").toString();
    req->carOwner   = content.toObject().value("CarOwner").toString();
    return req;
}
