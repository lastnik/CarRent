#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>

struct ChatInfoMsg: public IMsg
{
    Q_OBJECT
public:
    explicit ChatInfoMsg():IMsg()
    {
        IMsg::msgName = "ChatInfoMsg";
    }
    ~ChatInfoMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString carName;
    QString carOwner;
    QString userName;
};

IMsg* toChatInfoMsgStruct(QJsonDocument);

struct ChatInfoReq: public IReq
{
    Q_OBJECT
public:
    explicit ChatInfoReq():IReq()
    {
        IReq::reqName = "ChatInfoReq";
    }
    ~ChatInfoReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString                                  login;
    QString                                  carName;
    QString                                  carOwner;
    QString                                  userName;
    std::vector<std::pair<QString, QString>> chat;
};

IReq* toChatInfoReqStruct(QJsonDocument);

