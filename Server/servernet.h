#ifndef SERVERNET_H
#define SERVERNET_H

#include <QObject>
#include <memory>
#include "imsg.h"
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
#include "chatinfomsg.h"
#include "chatslistmsg.h"
#include "newmsgchatmsg.h"
#include <functional>
#include <map>
#include <vector>
class ServerNet : public QObject
{
    Q_OBJECT
public:
    explicit ServerNet(QObject *parent = nullptr);
signals:
    void receive(IMsg*);
    void receive(IReq*);
    void receiveAdmin(IMsg*);
    void transmitReq(IReq*);
    void transmitMsg(IMsg*);
public slots:
    void receive();
    void transmit(IReq*);
    void transmit(IMsg*);
    void scheduler(IMsg*);
    void scheduler(IReq*);
    void schedulerAdmin(IMsg*);
private:
    void schedulerReq(LoginMsg*);
    void creatNewFieldDataBase(QString);
    void schedulerReq(AccessMsg*);
    void schedulerReq(RegistrationMsg*);
    void schedulerReq(RegistrationReq*);
    void schedulerReq(RegistrationCarMsg*);
    void schedulerReq(RegistrationCarReq*);
    void schedulerReq(CarInfoMsg*);
    void schedulerReq(ConfirmRentalMsg*);
    void schedulerReq(RentalInfoMsg*);
    void schedulerReq(RentalListInfoMsg*);
    void schedulerReq(RentalRespondMsg*);
    void schedulerReq(ChatListMsg*);
    void schedulerReq(ChatInfoMsg*);
    void schedulerReq(NewMsgChatMsg*);
private:
    std::unique_ptr<server::ITransmiter> transmiter;
    std::unique_ptr<server::IReceiver>   receiver;
    std::map<QString, std::function<IMsg*(QJsonDocument)>> converterMsg;
    std::map<QString, std::function<IReq*(QJsonDocument)>> converterReq;
    std::vector<QString> msgNum;
    std::vector<QString> reqNum;
    std::vector<QString> documentsPersonName;
    std::vector<QString> documentsCarName;
};

#endif // SERVERNET_H
