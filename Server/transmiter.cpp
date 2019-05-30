#include "transmiter.h"
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDateTime>
namespace  server {

const char* wayReq = "C:/Qt/project/Server/req";
extern const char* wayMsg;

void FileTransmiter::transmit(IReq* req)
{
    QFile letter(wayReq + ("/" + req->reqName+ req->receiverName + ".json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    auto letterReq = req->toJsonObject();
    QJsonDocument doc(letterReq);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete req;
}

void FileTransmiter::transmit(IMsg* msg)
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


}
