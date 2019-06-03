#pragma once
#include "imsg.h"
#include <QObject>
#include <QJsonDocument>
#include <vector>
#include <utility>
class RegistrationCarMsg : public IMsg
{
    Q_OBJECT
public:
    explicit RegistrationCarMsg():IMsg()
    {
        IMsg::msgName = "RegistrationCarMsg";
    }
    ~RegistrationCarMsg(){}
    virtual QJsonObject toJsonObject() override;
public:
    std::vector<std::pair<QString, QString>> documents;
    QString                                  login;
    QString                                  carBrend;
    QString                                  carModel;
    QString                                  carColor;
    QString                                  carNumber;
    int                                      year;
};

IMsg* toRegistrationCarMsgStruct(QJsonDocument);

struct RegistrationCarReq: public IReq
{
    Q_OBJECT
public:
    explicit RegistrationCarReq():IReq()
    {
        IReq::reqName = "RegistrationCarReq";
    }
    ~RegistrationCarReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    bool    isCar;
    QString carName;
    QString login;
};

IReq* toRegistrationCarReqStruct(QJsonDocument);

