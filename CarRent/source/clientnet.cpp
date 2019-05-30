#include "clientnet.h"
#include "transmiter.h"
#include "receiver.h"
#include "loginmsg.h"
#include "accessmsg.h"
#include "registrationmsg.h"

#include <memory>
#include <QTimer>
QString ClientNet::login;

ClientNet::ClientNet(QObject *parent) : QObject(parent)
{
   transmiter = std::make_unique<FileTransmiter>();
   receiver   = std::make_unique<FileReceiver>();

   //registration
   reqNum.push_back("LoginReq");
   converter["LoginReq"] = toLoginReqStruct;

   reqNum.push_back("AccessReq");
   converter["AccessReq"] = toAccessReqStruct;

   reqNum.push_back("RegistrationReq");
   converter["RegistrationReq"] = toRegistrationReqStruct;

   QTimer::singleShot(1000, this, SLOT(receive()));
}
void ClientNet::transmit(IMsg* msg)
{
    transmiter->transmit(msg);
}

void ClientNet::receive()
{
    for(auto i : reqNum)
    {
        IReq* req = receiver->receive(i + login, converter.at(i));
        if(req != nullptr)
        {
            emit receive(req);
        }
    }
    QTimer::singleShot(1000, this, SLOT(receive()));
}

void ClientNet::setLogin(QString _login)
{
    login = _login;
}
