#include "transmiter.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
const QString wayMsg = QString(PATH) + "/../Server/msg";

void FileTransmiter::transmit(IMsg* msg)
{
    auto letterMsg = msg->toJsonObject();
    QFile letter(wayMsg + ("/" + msg->msgName + msg->transmiterName + ".json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument doc(letterMsg);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete msg;
}

