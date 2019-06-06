#pragma once
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>
#include "rentalinfomsg.h"
struct RentalListInfoMsg: public IMsg
{
    Q_OBJECT
public:
    explicit RentalListInfoMsg():IMsg()
    {
        IMsg::msgName = "RentalListInfoMsg";
    }
    ~RentalListInfoMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
    QString from;
    QString to;
};

IMsg* toRentalListInfoMsgStruct(QJsonDocument);

struct RentalListInfoReq: public IReq
{
    Q_OBJECT
public:
    explicit RentalListInfoReq():IReq()
    {
        IReq::reqName = "RentalListInfoReq";
    }
    ~RentalListInfoReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString                                  login;
    std::vector<RentalInfoReq*>              infoList;
};

IReq* toRentalListInfoReqStruct(QJsonDocument);
