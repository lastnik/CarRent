#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>

struct ChatListMsg: public IMsg
{
    Q_OBJECT
public:
    explicit ChatListMsg():IMsg()
    {
        IMsg::msgName = "ChatListMsg";
    }
    ~ChatListMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString carName;
    QString carOwner;
};

IMsg* toChatListMsgStruct(QJsonDocument);


struct ChatListReq: public IReq
{
    Q_OBJECT
public:
    explicit ChatListReq():IReq()
    {
        IReq::reqName = "ChatListReq";
    }
    ~ChatListReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString                                  login;
    QString                                  carName;
    QString                                  carOwner;
    std::vector<QString>                     userName;
};

IReq* toChatListReqStruct(QJsonDocument);

