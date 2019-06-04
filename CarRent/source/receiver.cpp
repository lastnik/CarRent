#include "receiver.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDir>
const QString wayReq = QString(PATH) + "/../Server/req";

IReq* FileReceiver::receive(QString reqName,  std::function<IReq*(QJsonDocument)>& fromJson)
{
    QDir dir(wayReq);
    auto list = dir.entryList(QStringList("*"), QDir::Files);
    for(auto i : list)
    {
        if( i.toStdString().find("Admin.json") == std::string::npos &&
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
