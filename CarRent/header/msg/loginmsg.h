#ifndef LOGINMSG_H
#define LOGINMSG_H
#include "imsg.h"
#include <QJsonDocument>
struct LoginMsg: public IMsg
{
    Q_OBJECT
public:
    explicit LoginMsg():IMsg()
    {
        IMsg::msgName = "LoginMsg";
    }
    ~LoginMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString password;
    bool isUser = false;
};

IMsg* toLoginMsgStruct(QJsonDocument);

struct LoginReq: public IReq
{
    Q_OBJECT
public:
    explicit LoginReq():IReq()
    {
        IReq::reqName = "LoginReq";
    }
    ~LoginReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString login;
    QString password;
    bool isUser = false;
    bool isCorrect = false;
};

IReq* toLoginReqStruct(QJsonDocument);


#endif // LOGINMSG_H
