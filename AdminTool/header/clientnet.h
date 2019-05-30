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
    void stop();
signals:
    void cancled();
    void receive(IReq*);
    void receive(IMsg*);
public slots:
    void receive();
    void transmit(IMsg*);
    void transmit(IReq*);
    void transmitMsgSaver(IMsg*);
private:
    std::unique_ptr<ITransmiter> transmiter;
    std::unique_ptr<IReceiver>   receiver;

    std::map<QString, std::function<IReq*(QJsonDocument)>> converterReq;
    std::map<QString, std::function<IMsg*(QJsonDocument)>> converterMsg;
    std::vector<QString> reqNum;
    std::vector<QString> msgNum;
    bool stopped = false;
    static QString login;
};

#endif // CLIENTNET_H
