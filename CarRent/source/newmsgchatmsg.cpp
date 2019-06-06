#include "newmsgchatmsg.h"
#include <QJsonArray>
QJsonObject NewMsgChatMsg::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
        {"CarName",    carName},
        {"From",       from},
        {"To",         to},
        {"Text",       text}
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

IMsg* toNewMsgChatMsgStruct(QJsonDocument doc)
{
    NewMsgChatMsg* msg = new NewMsgChatMsg();
    msg->msgName = "NewMsgChatMsg";
    auto content = doc.object().value("NewMsgChatMsg");
    msg->login   = content.toObject().value("Login").toString();
    msg->carName = content.toObject().value("CarName").toString();
    msg->from    = content.toObject().value("From").toString();
    msg->to      = content.toObject().value("To").toString();
    msg->text    = content.toObject().value("Text").toString();
    msg->transmiterName = msg->login;
    return msg;
}

QJsonObject NewMsgChatReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",      login},
        {"CarName",    carName},
        {"From",       from},
        {"To",         to},
        {"Text",       text}
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

IReq* toNewMsgChatReqStruct(QJsonDocument doc)
{
    NewMsgChatReq* req = new NewMsgChatReq();
    req->reqName = "NewMsgChatReq";
    auto content = doc.object().value("NewMsgChatReq");
    req->login   = content.toObject().value("Login").toString();
    req->carName = content.toObject().value("CarName").toString();
    req->from    = content.toObject().value("From").toString();
    req->to      = content.toObject().value("To").toString();
    req->text    = content.toObject().value("Text").toString();
    req->receiverName = req->login;
    return req;
}
