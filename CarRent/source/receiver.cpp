#include "receiver.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

const char* wayReq = "C:/Qt/project/Server/req";

IReq* FileReceiver::receive(QString reqName,  std::function<IReq*(QJsonDocument)>& fromJson)
{
    QFile letter(wayReq + ("/" + reqName + ".json"));
    if(letter.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = letter.readAll();
        letter.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        letter.remove();
        return fromJson(doc);
    }
    return nullptr;
}
