#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>

struct RentalInfoMsg: public IMsg
{
    Q_OBJECT
public:
    explicit RentalInfoMsg():IMsg()
    {
        IMsg::msgName = "RentalInfoMsg";
    }
    ~RentalInfoMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString carName;
};

IMsg* toRentalInfoMsgStruct(QJsonDocument);

struct RentalInfoReq: public IReq
{
    Q_OBJECT
public:
    explicit RentalInfoReq():IReq()
    {
        IReq::reqName = "RentalInfoReq";
    }
    ~RentalInfoReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString                                  login;
    QString                                  carName;
    QString                                  from;
    QString                                  to;
    QString                                  rentUser;
    double                                   cost;
};

IReq* toRentalInfoReqStruct(QJsonDocument);

