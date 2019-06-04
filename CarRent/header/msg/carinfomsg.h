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
    QString                                  login;
    QString                                  carName;
    bool                                     isCar;
    std::vector<std::pair<QString, QString>> documents;
    QString                                  carBrend;
    QString                                  carModel;
    QString                                  carColor;
    QString                                  carNumber;
    QString                                  carOwner;
    QString                                  carState;
    int                                      year;
};

IReq* toCarInfoReqStruct(QJsonDocument);

