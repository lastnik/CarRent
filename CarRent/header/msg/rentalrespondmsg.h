#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>

struct RentalRespondMsg: public IMsg
{
    Q_OBJECT
public:
    explicit RentalRespondMsg():IMsg()
    {
        IMsg::msgName = "RentalRespondMsg";
    }
    ~RentalRespondMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString carName;
    QString carOwner;
    QString rentalUser;
};

IMsg* toRentalRespondMsgStruct(QJsonDocument);

struct RentalRespondReq: public IReq
{
    Q_OBJECT
public:
    explicit RentalRespondReq():IReq()
    {
        IReq::reqName = "RentalRespondReq";
    }
    ~RentalRespondReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString login;
    QString carName;
    QString carOwner;
    QString rentalUser;
};

IReq* toRentalRespondReqStruct(QJsonDocument);

