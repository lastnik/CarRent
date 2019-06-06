#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>

struct NewMsgChatMsg: public IMsg
{
    Q_OBJECT
public:
    explicit NewMsgChatMsg():IMsg()
    {
        IMsg::msgName = "NewMsgChatMsg";
    }
    ~NewMsgChatMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString from;
    QString carName;
    QString to;
    QString text;
};

IMsg* toNewMsgChatMsgStruct(QJsonDocument);

struct NewMsgChatReq: public IReq
{
    Q_OBJECT
public:
    explicit NewMsgChatReq():IReq()
    {
        IReq::reqName = "NewMsgChatReq";
    }
    ~NewMsgChatReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString login;
    QString from;
    QString to;
    QString text;
    QString carName;
};

IReq* toNewMsgChatReqStruct(QJsonDocument);

