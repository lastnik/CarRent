#include "transmiter.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDateTime>
QString wayMsg = QString(PATH) + "/../Server/msg";
extern QString wayReq;
void FileTransmiter::transmit(IMsg* msg)
{
    QFile letter(wayMsg + ("/" + msg->msgName + "Admin.json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    auto letterMsg = msg->toJsonObject();
    QJsonDocument doc(letterMsg);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete msg;
}

void FileTransmiter::transmit(IReq* req)
{
    QFile letter(wayReq + ("/" + req->reqName + QDateTime::currentDateTime().toString("ddMMhhmmsszzz") + "Admin.json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    auto letterMsg = req->toJsonObject();
    QJsonDocument doc(letterMsg);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete req;
}

void FileTransmiter::transmitSaver(IMsg* msg)
{
    QFile letter(wayMsg + ("/" + msg->msgName + QDateTime::currentDateTime().toString("ddMMhhmmsszzz") + "Admin.json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    auto letterMsg = msg->toJsonObject();
    QJsonDocument doc(letterMsg);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete msg;
}
