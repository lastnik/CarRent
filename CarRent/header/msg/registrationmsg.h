#ifndef REGISTRATIONMSG_H
#define REGISTRATIONMSG_H

#include "imsg.h"
#include <QObject>
#include <QJsonDocument>
#include <vector>
#include <utility>
class RegistrationMsg : public IMsg
{
    Q_OBJECT
public:
    explicit RegistrationMsg():IMsg()
    {
        IMsg::msgName = "RegistrationMsg";
    }
    ~RegistrationMsg(){}
    virtual QJsonObject toJsonObject() override;
public:
    std::vector<std::pair<QString, QString>> documents;
    QString                                  login;
};

IMsg* toRegistrationMsgStruct(QJsonDocument);

struct RegistrationReq: public IReq
{
    Q_OBJECT
public:
    explicit RegistrationReq():IReq()
    {
        IReq::reqName = "RegistrationReq";
    }
    ~RegistrationReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    bool    isPerson;
    QString login;
};

IReq* toRegistrationReqStruct(QJsonDocument);


#endif // REGISTRATIONMSG_H
