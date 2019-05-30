#ifndef CLIENTNET_H
#define CLIENTNET_H

#include <QObject>
#include <memory>
#include "imsg.h"
#include "transmiter.h"
#include "receiver.h"
#include <functional>
#include <map>
#include <vector>
class ClientNet : public QObject
{
    Q_OBJECT
public:
    explicit ClientNet(QObject *parent = nullptr);
    static void setLogin(QString);
signals:
    void cancled();
    void receive(IReq*);
public slots:
    void receive();
    void transmit(IMsg*);
private:
    std::unique_ptr<ITransmiter> transmiter;
    std::unique_ptr<IReceiver>   receiver;

    std::map<QString, std::function<IReq*(QJsonDocument)>> converter;
    std::vector<QString> reqNum;

    static QString login;
    int numCycleWaitLogin = 5;
};

#endif // CLIENTNET_H
