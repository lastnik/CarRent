#include "clientnet.h"
#include "transmiter.h"
#include "receiver.h"
#include "loginmsg.h"
#include "accessmsg.h"
#include "registrationmsg.h"
#include "registrationcarmsg.h"
#include "carinfomsg.h"
#include "confirmrentalmsg.h"
#include "rentalinfomsg.h"
#include "rentallistinfomsg.h"
#include "rentalrespondmsg.h"
#include "chatslistmsg.h"
#include "chatinfomsg.h"
#include "newmsgchatmsg.h"


#include <memory>
#include <QTimer>
QString ClientNet::login = "____________________________________________";

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

   reqNum.push_back("RegistrationCarReq");
   converter["RegistrationCarReq"] = toRegistrationCarReqStruct;

   reqNum.push_back("CarInfoReq");
   converter["CarInfoReq"] = toCarInfoReqStruct;

   reqNum.push_back("ConfirmRentalReq");
   converter["ConfirmRentalReq"] = toConfirmRentalReqStruct;

   reqNum.push_back("RentalInfoReq");
   converter["RentalInfoReq"] = toRentalInfoReqStruct;

   reqNum.push_back("RentalListInfoReq");
   converter["RentalListInfoReq"] = toRentalListInfoReqStruct;

   reqNum.push_back("RentalRespondReq");
   converter["RentalRespondReq"] = toRentalRespondReqStruct;

   reqNum.push_back("ChatListReq");
   converter["ChatListReq"] = toChatListReqStruct;

   reqNum.push_back("ChatInfoReq");
   converter["ChatInfoReq"] = toChatInfoReqStruct;

   reqNum.push_back("NewMsgChatReq");
   converter["NewMsgChatReq"] = toNewMsgChatReqStruct;


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
