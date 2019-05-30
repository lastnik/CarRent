#ifndef RECEIVER_H
#define RECEIVER_H
#include "imsg.h"
#include <functional>
namespace  server {
class IReceiver
{
public:

    virtual IMsg* receive(QString, std::function<IMsg*(QJsonDocument)>&)=0;
    virtual IReq* receive(QString, std::function<IReq*(QJsonDocument)>&)=0;
    virtual IMsg* receiveAdmin(QString, std::function<IMsg*(QJsonDocument)>&)=0;
};

class FileReceiver : public IReceiver
{
public:
    explicit FileReceiver():IReceiver(){}
    virtual ~FileReceiver(){}

    virtual IMsg* receive(QString msgName, std::function<IMsg*(QJsonDocument)>&) final;
    virtual IReq* receive(QString reqName, std::function<IReq*(QJsonDocument)>&) final;
    virtual IMsg* receiveAdmin(QString msgName, std::function<IMsg*(QJsonDocument)>&) final;
};
}
#endif // RECEIVER_H
