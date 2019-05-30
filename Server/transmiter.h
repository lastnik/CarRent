#ifndef TRANSMITER_H
#define TRANSMITER_H
#include "imsg.h"
namespace  server {
class ITransmiter
{
public:
    virtual void transmit(IReq*)=0;
    virtual void transmit(IMsg*)=0;
};

class FileTransmiter : public ITransmiter
{
public:
    explicit FileTransmiter():ITransmiter(){}
    virtual ~FileTransmiter(){}
    virtual void transmit(IReq*) final;
    virtual void transmit(IMsg*) final;
};
}
#endif // TRANSMITER_H
