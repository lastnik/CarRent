#ifndef TRANSMITER_H
#define TRANSMITER_H
#include "IMsg.h"
class ITransmiter
{
public:
    virtual void transmit(IMsg*)=0;
};

class FileTransmiter : public ITransmiter
{
public:
    explicit FileTransmiter():ITransmiter(){}
    virtual ~FileTransmiter(){}
    virtual void transmit(IMsg*) final;
};

#endif // TRANSMITER_H
