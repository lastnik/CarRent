#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "loginmsg.h"
#include "registrationmsg.h"
#include "registrationcarmsg.h"
#include "accessmsg.h"
#include "carmodel.h"

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
    void setCars(std::vector<CarParam>);
    void addCar(CarParam);
    void error(int errorCode);
public slots:
    void receiveReq(IReq*);
    void accessInfo();
    void start(LoginReq*);
    void confirmDocs(std::vector<std::pair<QString, QString>>);
    void transmitCarInfoMsg(QString);
private:
    void scheduler(AccessReq* req);
    void scheduler(RegistrationReq* req);
    void scheduler(RegistrationCarReq* req);
    QObject *root = nullptr;
    QString         login;
};

#endif // CORE_H
