#include "transmiter.h"
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDateTime>
namespace  server {

QString wayReq = QString(PATH) + "/req";
extern QString wayMsg;

void FileTransmiter::transmit(IReq* req)
{
    auto letterReq = req->toJsonObject();
    QFile letter(wayReq + ("/" + req->reqName+ req->receiverName + QDateTime::currentDateTime().toString("ddMMhhmmsszzz") + ".json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument doc(letterReq);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete req;
}

void FileTransmiter::transmit(IMsg* msg)
{
    auto letterMsg = msg->toJsonObject();
    QFile letter(wayMsg + ("/" + msg->msgName + QDateTime::currentDateTime().toString("ddMMhhmmsszzz") + "Admin.json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument doc(letterMsg);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete msg;
}


}
