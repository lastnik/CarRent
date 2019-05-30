#include "transmiter.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
const char* wayMsg = "C:/Qt/project/Server/msg";

void FileTransmiter::transmit(IMsg* msg)
{
    QFile letter(wayMsg + ("/" + msg->msgName + ".json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    auto letterMsg = msg->toJsonObject();
    QJsonDocument doc(letterMsg);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete msg;
}

