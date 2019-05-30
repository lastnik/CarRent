#ifndef RECEIVER_H
#define RECEIVER_H
#include "IMsg.h"
#include <functional>
class IReceiver
{
public:

    virtual IReq* receive(QString,  std::function<IReq*(QJsonDocument)>&)=0;
    virtual IMsg* receive(QString,  std::function<IMsg*(QJsonDocument)>&)=0;
};

class FileReceiver : public IReceiver
{
public:
    explicit FileReceiver():IReceiver(){}
    virtual ~FileReceiver(){}

    virtual IReq* receive(QString,  std::function<IReq*(QJsonDocument)>&) final;
    virtual IMsg* receive(QString,  std::function<IMsg*(QJsonDocument)>&) final;
};
#endif // RECEIVER_H
