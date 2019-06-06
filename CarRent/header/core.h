#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "loginmsg.h"
#include "registrationmsg.h"
#include "registrationcarmsg.h"
#include "accessmsg.h"
#include "carmodel.h"
#include "rentaladmodel.h"
#include "carinfomsg.h"
#include "confirmrentalmsg.h"
#include "rentalinfomsg.h"
#include "rentallistinfomsg.h"
#include "rentalrespondmsg.h"
#include "chatslistmsg.h"
#include "chatinfomsg.h"
#include "chatlistmodel.h"
#include "chatmodel.h"
#include "newmsgchatmsg.h"
class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    void setRoot(QObject *);
signals:
    void transmitMsg(IMsg*);
    void receive(IReq*);
    void setDocName(QStringList);
    void waitingConfirm();
    // list model documents
    void add(int id, QString name, bool vis);
    void pop();
    void clear();
    void clearCar();
    void setCars(std::vector<CarParam>);
    void setRentalAd(std::vector<RentalAd>);
    void addCar(CarParam);
    void addCarRentalAd(CarRentalAd);
    void error(int errorCode);
    void seeCarPage();

    //chats
    void addChatInfo(QString from, QString to);
    void setChat(QString from, QString to, std::vector<Message> params);
    void loadMsg(Message);
    void zeroChat();
    void clearListChat();
public slots:
    void rentalMsg(QString, QString, double);
    void receiveReq(IReq*);
    void accessInfo();
    void rentalListInfo();
    void start(LoginReq*);
    void confirmDocs(std::vector<std::pair<QString, QString>>);
    void transmitCarInfoMsg(QString);
    void see(QString);
    void rentalRespond(QString carOwner, QString carName);
    void atemptRespond(bool);
    //chats
    void chatUpdateList(QString carName, QString carOwner);
    void pushMsg(Message, QString);
private:
    void scheduler(AccessReq*          req);
    void scheduler(RegistrationReq*    req);
    void scheduler(RegistrationCarReq* req);
    void scheduler(CarInfoReq*         req);
    void scheduler(ConfirmRentalReq*   req);
    void scheduler(RentalInfoReq*      req);
    void scheduler(RentalListInfoReq*  req);
    void scheduler(RentalRespondReq*   req);
    void scheduler(ChatListReq*        req);
    void scheduler(ChatInfoReq*        req);
    void scheduler(NewMsgChatReq*      req);
    QObject *root = nullptr;
    QString         login;
    bool            isPerson   = false;
    bool            seeInfoCar = false;
    bool            seeInfoRental = false;
    bool            chatReady     = false;
    RentalRespondReq *reqs = nullptr;
};

#endif // CORE_H
