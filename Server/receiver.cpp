#include "receiver.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDir>
namespace  server {
QString wayMsg = QString(PATH) + "/msg";
extern QString wayReq;
IMsg* FileReceiver::receive(QString msgName, std::function<IMsg*(QJsonDocument)>& fromJson)
{
    QDir dir(wayMsg);
    auto list = dir.entryList(QStringList("*"), QDir::Files);
    for(auto i : list)
    {
        if(i.toStdString().find(msgName.toStdString()) != std::string::npos
                && i.toStdString().find("Admin.json")  == std::string::npos)
        {
            QFile letter(wayMsg + ("/" + i));
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
    }
    return nullptr;
}
IReq* FileReceiver::receive(QString reqName, std::function<IReq*(QJsonDocument)>& fromJson)
{
    QDir dir(wayReq);
    auto list = dir.entryList(QStringList("*"), QDir::Files);
    for(auto i : list)
    {
        if( i.toStdString().find("Admin.json") != std::string::npos &&
            i.toStdString().find(reqName.toStdString()) != std::string::npos)
        {
            QFile letter(wayReq + ("/" + i));
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
    }
    return nullptr;
}

IMsg* FileReceiver::receiveAdmin(QString msgName, std::function<IMsg*(QJsonDocument)>& fromJson)
{
    QFile letter(wayMsg + ("/" + msgName + "Admin.json"));
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


}
