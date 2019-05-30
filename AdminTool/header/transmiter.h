#ifndef TRANSMITER_H
#define TRANSMITER_H
#include "IMsg.h"

class ITransmiter
{
public:
    virtual void transmit(IMsg*)=0;
    virtual void transmit(IReq*)=0;
    virtual void transmitSaver(IMsg*)=0;
};

class FileTransmiter : public ITransmiter
{
public:
    explicit FileTransmiter():ITransmiter(){}
    virtual ~FileTransmiter(){}
    virtual void transmit(IMsg*) final;
    virtual void transmit(IReq*) final;
    virtual void transmitSaver(IMsg*) final;
};

#endif // TRANSMITER_H
