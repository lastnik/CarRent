#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>

struct ConfirmRentalMsg: public IMsg
{
    Q_OBJECT
public:
    explicit ConfirmRentalMsg():IMsg()
    {
        IMsg::msgName = "ConfirmRentalMsg";
    }
    ~ConfirmRentalMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString carName;
    double  cost;
    QString from;
    QString to;
};

IMsg* toConfirmRentalMsgStruct(QJsonDocument);

struct ConfirmRentalReq: public IReq
{
    Q_OBJECT
public:
    explicit ConfirmRentalReq():IReq()
    {
        IReq::reqName = "ConfirmRentalReq";
    }
    ~ConfirmRentalReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString login;
    QString carName;
    bool    result;
};

IReq* toConfirmRentalReqStruct(QJsonDocument);
