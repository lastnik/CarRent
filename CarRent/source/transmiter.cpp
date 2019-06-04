#include "transmiter.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDateTime>
const QString wayMsg = QString(PATH) + "/../Server/msg";

void FileTransmiter::transmit(IMsg* msg)
{
    auto letterMsg = msg->toJsonObject();
    QFile letter(wayMsg + ("/" + msg->msgName + msg->transmiterName + QDateTime::currentDateTime().toString("ddMMhhmmsszzz") + ".json"));
    letter.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument doc(letterMsg);
    auto val = doc.toJson();
    letter.write(val);
    letter.close();
    delete msg;
}

