#include "loginmsg.h"

QJsonObject LoginMsg::toJsonObject()
{   
    QJsonObject obj
    {
        {"Login",    login},
        {"Password", password},
        {"isUser",   isUser}
    };
    QJsonObject total
    {
        {
            msgName, obj
        }
    };
    return total;
};

IMsg* toLoginMsgStruct(QJsonDocument doc)
{
    LoginMsg* msg = new LoginMsg();
    msg->msgName = "LoginMsg";
    auto content = doc.object().value("LoginMsg");
    msg->login = content.toObject().value("Login").toString();
    msg->password = content.toObject().value("Password").toString();
    msg->isUser = content.toObject().value("isUser").toBool();
    return msg;
}

QJsonObject LoginReq::toJsonObject()
{
    QJsonObject obj
    {
        {"Login",     login},
        {"Password",  password},
        {"isUser",    isUser},
        {"isCorrect", isCorrect}
    };
    QJsonObject total
    {
        {
            reqName, obj
        }
    };
    return total;
};

IReq* toLoginReqStruct(QJsonDocument doc)
{
    LoginReq* req  = new LoginReq();
    req->reqName   = "LoginReq";
    auto content   = doc.object().value("LoginReq");
    req->login     = content.toObject().value("Login").toString();
    req->password  = content.toObject().value("Password").toString();
    req->isUser    = content.toObject().value("isUser").toBool();
    req->isCorrect = content.toObject().value("isCorrect").toBool();
    req->receiverName = req->login;
    return req;
}
