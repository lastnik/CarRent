#include "clientnet.h"
#include "transmiter.h"
#include "receiver.h"
#include "loginmsg.h"
#include "accessmsg.h"
#include "registrationmsg.h"

#include <memory>
#include <QTimer>
QString  ClientNet::login;
ClientNet::ClientNet(QObject *parent) : QObject(parent)
{
   transmiter = std::make_unique<FileTransmiter>();
   receiver   = std::make_unique<FileReceiver>();

   //registration
   reqNum.push_back("LoginReq");
   converterReq["LoginReq"] = toLoginReqStruct;

   msgNum.push_back("RegistrationMsg");
   converterMsg["RegistrationMsg"] = toRegistrationMsgStruct;

   QTimer::singleShot(1000, this, SLOT(receive()));
}
void ClientNet::transmit(IMsg* msg)
{
    transmiter->transmit(msg);
}

void ClientNet::transmit(IReq* req)
{
    transmiter->transmit(req);
}

void ClientNet::transmitMsgSaver(IMsg* msg)
{
    transmiter->transmitSaver(msg);
}
void ClientNet::stop()
{
    stopped = true;
}
void ClientNet::receive()
{
    if(stopped) return;
    for(auto i : reqNum)
    {
        do{
            IReq* req = receiver->receive(i, converterReq.at(i));
            if(req != nullptr)
            {
                emit receive(req);
            }else
            {
                break;
            }
        }while(true);
    }
    for(auto i : msgNum)
    {
        do{
            IMsg* msg = receiver->receive(i, converterMsg.at(i));
            if(msg != nullptr)
            {
                emit receive(msg);
            }else
            {
                break;
            }
        }while(true);
    }
    QTimer::singleShot(1000, this, SLOT(receive()));
}

void ClientNet::setLogin(QString _login)
{
    login = _login;
}
