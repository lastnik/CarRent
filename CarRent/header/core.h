#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "loginmsg.h"
#include "registrationmsg.h"
#include "accessmsg.h"
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
    void clear();

public slots:
    void receiveReq(IReq*);
    void accessInfo();
    void start(LoginReq*);
    void confirmDocs(std::vector<std::pair<QString, QString>>);
private:
    void scheduler(AccessReq* req);
    void scheduler(RegistrationReq* req);
    QObject *root = nullptr;
    QString         login;
};

#endif // CORE_H
