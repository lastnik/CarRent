#ifndef ACCESSMSG_H
#define ACCESSMSG_H
#include "imsg.h"
#include <QJsonDocument>
#include <vector>
#include <utility>
struct AccessMsg: public IMsg
{
    Q_OBJECT
public:
    explicit AccessMsg():IMsg()
    {
        IMsg::msgName = "AccessMsg";
    }
    ~AccessMsg(){}
    virtual QJsonObject toJsonObject() override;
public: //fields
    QString login;
};

IMsg* toAccessMsgStruct(QJsonDocument);

struct AccessReq: public IReq
{
    Q_OBJECT
public:
    explicit AccessReq():IReq()
    {
        IReq::reqName = "AccessReq";
    }
    ~AccessReq(){}
    virtual QJsonObject toJsonObject() override;

public: //fields
    QString login;
    bool    isPerson;
    std::vector<std::pair<QString, bool>> documents;
    bool    hasCars;
    std::vector<QString> carsNames;
};

IReq* toAccessReqStruct(QJsonDocument);


#endif // ACCESSMSG_H
