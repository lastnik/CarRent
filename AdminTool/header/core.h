#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "loginmsg.h"
#include "registrationmsg.h"
#include "registrationcarmsg.h"
#include "accessmsg.h"
#include "imsg.h"
#include <vector>
#include <utility>
class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    void setRoot(QObject *);
    void save();
signals:
    void transmitReq(IReq*);
    void transmitMsgSaver(IMsg*);
    void receive(IReq*);
    void erase(int totalReq);
    // list model documents
    void add(QString userName, QString type);
    void addDoc(QString docName, QString docSource);
    void clearDoc();

public slots:
    void receiveMsg(IMsg*);
    void receiveReq(IReq*);
    void start(LoginReq*);
    void event(int);
    void sendResponce(int,int,int);
private:
    void schedulerReq(RegistrationMsg*);
    void schedulerReq(RegistrationCarMsg*);
    QObject *root = nullptr;
    std::vector<RegistrationMsg*>                historyPerson;
    std::vector<RegistrationCarMsg*>             historyCar;
    std::vector<std::pair<QString, int>>         total;
};

#endif // CORE_H
