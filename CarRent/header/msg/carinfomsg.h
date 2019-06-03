#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>

struct CarInfoMsg: public IMsg
{
    Q_OBJECT
public:
    explicit CarInfoMsg():IMsg()
    {
        IMsg::msgName = "CarInfoMsg";
    }
    ~CarInfoMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString carName;
};

IMsg* toCarInfoMsgStruct(QJsonDocument);

struct CarInfoReq: public IReq
{
    Q_OBJECT
public:
    explicit CarInfoReq():IReq()
    {
        IReq::reqName = "CarInfoReq";
    }
    ~CarInfoReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields

};

IReq* toCarInfoReqStruct(QJsonDocument);

