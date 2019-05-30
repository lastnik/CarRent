#include "servernet.h"
#include <QTimer>
#include <typeinfo>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>
const char* wayData = "C:/Qt/project/Server/data";

ServerNet::ServerNet(QObject *parent) : QObject(parent)
{
    transmiter = std::make_unique<server::FileTransmiter>();
    receiver   = std::make_unique<server::FileReceiver>();
    connect(this,SIGNAL(receive(IMsg*)),this,SLOT(scheduler(IMsg*)));
    connect(this,SIGNAL(receive(IReq*)),this,SLOT(scheduler(IReq*)));
    connect(this,SIGNAL(receiveAdmin(IMsg*)),this,SLOT(schedulerAdmin(IMsg*)));
    connect(this,SIGNAL(transmitReq(IReq*)),this,SLOT(transmit(IReq*)));
    connect(this,SIGNAL(transmitMsg(IMsg*)),this,SLOT(transmit(IMsg*)));
    //registration msg
    msgNum.push_back("LoginMsg");
    converterMsg["LoginMsg"] = toLoginMsgStruct;

    msgNum.push_back("AccessMsg");
    converterMsg["AccessMsg"] = toAccessMsgStruct;

    msgNum.push_back("RegistrationMsg");
    converterMsg["RegistrationMsg"] = toRegistrationMsgStruct;

    //registration req
    reqNum.push_back("RegistrationReq");
    converterReq["RegistrationReq"] = toRegistrationReqStruct;

    documentsPersonName.push_back("Passport");
    documentsPersonName.push_back("Driver Licence");

    QTimer::singleShot(1000, this, SLOT(receive()));
}




void ServerNet::receive()
{
    qDebug() << "Server: Start Receiving messages";
    for(auto i : msgNum)
    {
        do{
            IMsg* msg = receiver->receive(i, converterMsg.at(i));
            if(msg != nullptr)
            {
                qDebug() << "Server: Receive msg - " << i;
                emit receive(msg);
            }else
            {
                break;
            }
        }while(true);
    }
    //ADMIN
    IMsg* msg = receiver->receiveAdmin("LoginMsg",converterMsg.at("LoginMsg"));
    if(msg != nullptr)
    {
        qDebug() << "Server: Receive msg - " << "LoginMsg";
        emit receiveAdmin(msg);
    }
    qDebug() << "Server: Stop Receiving messages" << endl;
    qDebug() << "Server: Start Receiving requests";
    for(auto i : reqNum)
    {
        do{
            IReq* req = receiver->receive(i, converterReq.at(i));
            if(req != nullptr)
            {
                qDebug() << "Server: Receive Req - " << i;
                emit receive(req);
            }else
            {
                break;
            }
        }while(true);
    }
    qDebug() << "Server: Stop Receiving requests" << endl;
    QTimer::singleShot(1000, this, SLOT(receive()));
}

void ServerNet::scheduler(IMsg* msg)
{
    if(typeid (*msg).name() == typeid (LoginMsg).name())
    {
        schedulerReq(reinterpret_cast<LoginMsg*>(msg));
        return;
    }
    if(typeid (*msg).name() == typeid (AccessMsg).name())
    {
        schedulerReq(reinterpret_cast<AccessMsg*>(msg));
        return;
    }
    if(typeid (*msg).name() == typeid (RegistrationMsg).name())
    {
        schedulerReq(reinterpret_cast<RegistrationMsg*>(msg));
        return;
    }
}

void ServerNet::scheduler(IReq* req)
{
    if(typeid (*req).name() == typeid (RegistrationReq).name())
    {
        schedulerReq(reinterpret_cast<RegistrationReq*>(req));
        return;
    }
}

void ServerNet::schedulerAdmin(IMsg* msg)
{
    if(typeid (*msg).name() != typeid (LoginMsg).name())
    {
        qDebug() << "Server:  unsuccessful login attempt of Admin" << endl;
        return;
    }
    LoginMsg* _msg = reinterpret_cast<LoginMsg*>(msg);
    LoginReq* req = new LoginReq();
    if(_msg->login == "Admin" && _msg->password == "Admin")
    {
        req->reqName = "LoginReq";
        req->receiverName = _msg->login;
        req->login = _msg->login;
        req->password = _msg->password;
        req->isUser = _msg->isUser;
        qDebug() << "Server: successful login attempt of Admin";
        req->isCorrect = true;
    }else
    {
        req->reqName = "LoginReq";
        req->receiverName = _msg->login;
        req->login = _msg->login;
        req->password = _msg->password;
        req->isUser = _msg->isUser;
        qDebug() << "Server: unsuccessful login attempt of Admin";
        req->isCorrect = false;
    }
    emit transmitReq(req);
}

void ServerNet::schedulerReq(LoginMsg * msg)
{
    QFile data(wayData + ("/" + QString("Users") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        LoginReq* req = new LoginReq();
        req->reqName = "LoginReq";
        req->receiverName = msg->login;
        req->login = msg->login;
        req->password = msg->password;
        req->isUser = msg->isUser;
        bool isUs = false;

        bool isPas = false; //password ircorrect
        auto val = data.readAll();
        data.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("User").toArray();
        if(array.size() == 0)
        {
        }else
        {

            for (QJsonArray::iterator it = array.begin(); it!= array.end(); it++)
            {
                if(it->toObject().value("Login").toString() == msg->login && it->toObject().value("Password").toString() == msg->password)
                {
                    isUs = true;
                    break;
                }else
                {
                    if(it->toObject().value("Login").toString() == msg->login)
                    {
                        isPas = true;
                        break;
                    }
                }
            }
        }
        if(isUs != msg->isUser)
        {
            req->isCorrect = false;
            qDebug() << "Server: unsuccessful login attempt of User: " << msg->login;
        }
        else if(!isUs && !isPas)
        {
            QJsonObject obj{
                {"Login",    msg->login},
                {"Password", msg->password},
            };
            qDebug() << "Server: Registration new User: " << msg->login;
            QJsonValue val(obj);
            array.push_back(val);
            data.remove();
            data.open(QIODevice::WriteOnly | QIODevice::Text);

            QJsonObject all
            {
                {"User", array}
            };
            QJsonDocument newDoc(all);
            data.write(newDoc.toJson());
            data.close();
            creatNewFieldDataBase(msg->login);
            req->isCorrect = true;
        }else
        {
            if(isUs && !isPas)
            {
                qDebug() << "Server: successful login attempt of User: " << msg->login;
                req->isCorrect = true;
            }else
            {
                req->isCorrect = false;
                qDebug() << "Server: unsuccessful login attempt of User: " << msg->login;
            }
        }
        delete msg;
        emit transmitReq(req);
    }
}
void ServerNet::creatNewFieldDataBase(QString login)
{
    QFile data(wayData + ("/" + QString("Access") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = data.readAll();
        data.close();
        data.open(QIODevice::WriteOnly | QIODevice::Text);

        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("User").toArray();
        for(auto i : array)
        {
            if(i.toObject().value("Login").toString() == login)
            return;
        }
        QJsonObject obj
        {
            {"Login", login}
        };
        obj.insert("confirmPerson", false);
        QJsonArray person;
        for(auto i : documentsPersonName)
        {
            QJsonObject value
            {
                {"DocumentsName", i},
                {"DocumentsConfirm", false},
                {"DocumentsFileName", ""}
            };
            person.push_back(value);
        }
        obj.insert("PersonalDocuments", person);
        obj.insert("hasCars", false);
        QJsonArray cars;
        obj.insert("CarNames", cars);
        array.push_back(obj);
        QJsonObject all
        {
            {"User", array}
        };
        QJsonDocument newDoc(all);
        data.write(newDoc.toJson());
        data.close();
    }
}
void ServerNet::schedulerReq(AccessMsg* msg)
{
    QFile data(wayData + ("/" + QString("Access") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = data.readAll();
        data.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("User").toArray();
        for(auto i : array)
        {
            if(i.toObject().value("Login").toString() == msg->login)
            {
                AccessReq* req = new AccessReq();
                req->reqName = "AccessReq";
                req->receiverName = msg->login;
                req->login = msg->login;
                req->isPerson = i.toObject().value("confirmPerson").toBool();
                req->hasCars  = i.toObject().value("hasCars").toBool();
                auto person = i.toObject().value("PersonalDocuments").toArray();
                for(auto j : person)
                {
                    req->documents.push_back(std::make_pair( j.toObject().value("DocumentsName").toString()
                                                           , j.toObject().value("DocumentsConfirm").toBool()));
                }
                auto cars = i.toObject().value("CarNames").toArray();
                for(auto j : cars)
                {
                    req->carsNames.push_back(j.toString());
                }
                qDebug() << "Server: provide access for login: " << msg->login;
                emit transmitReq(req);
                delete msg;
                return;
            }
        }
    }
    qDebug() << "Server: unsuccessful access for login: " << msg->login;
    delete msg;
}
void ServerNet::schedulerReq(RegistrationMsg* msg)
{
    for(auto i : msg->documents)
    {
        QFile::copy("C:/Qt/project/Server/msg/" + i.second, "C:/Qt/project/Server/data/pics/" + i.second);
        QFile::remove("C:/Qt/project/Server/msg/" + i.second);
    }
    QFile data(wayData + ("/" + QString("Access") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = data.readAll();
        data.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("User").toArray();
        QJsonArray correct;
        for(auto i : array)
        {
            if(i.toObject().value("Login").toString() == msg->login)
            {
                qDebug() << "Server: correct cell in DataBase for user: " << msg->login;
                QJsonObject obj
                {
                    {"Login", msg->login}
                };
                obj.insert("confirmPerson", i.toObject().value("confirmPerson"));
                obj.insert("hasCars", i.toObject().value("hasCars"));
                obj.insert("CarNames", i.toObject().value("CarNames"));
                QJsonArray personNew;
                auto person = i.toObject().value("PersonalDocuments").toArray();
                for(auto j : person)
                {
                    bool is = false;
                    for(auto item : msg->documents)
                    {
                        if(j.toObject().value("DocumentsName").toString() == item.first)
                        {
                            qDebug() << "Server: correct feild PersonalDocuments for DocumentsName: " << item.first;
                            is = true;
                            QJsonObject value
                            {
                                {"DocumentsName", item.first},
                                {"DocumentsConfirm", true},
                                {"DocumentsFileName", item.second}
                            };
                            personNew.push_back(value);
                            break;
                        }
                    }
                    if(!is)
                    {
                        personNew.push_back(j);
                    }
                }
                obj.insert("PersonalDocuments",personNew);
                correct.push_back(obj);
            }else
            {
                correct.push_back(i);
            }
        }
        emit transmitMsg(msg);
        QJsonObject all
        {
            {"User", correct}
        };
        QJsonDocument newDoc(all);
        data.open(QIODevice::WriteOnly | QIODevice::Text);
        data.write(newDoc.toJson());
        data.close();
    }
}
void ServerNet::schedulerReq(RegistrationReq* req)
{
    QFile data(wayData + ("/" + QString("Access") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = data.readAll();
        data.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("User").toArray();
        QJsonArray correct;
        for(auto i : array)
        {
            if(i.toObject().value("Login").toString() == req->login)
            {
                qDebug() << "Server: correct cell in DataBase for user: " << req->login;
                QJsonObject obj
                {
                    {"Login", req->login}
                };
                obj.insert("confirmPerson", req->isPerson);
                obj.insert("hasCars", i.toObject().value("hasCars"));
                obj.insert("CarNames", i.toObject().value("CarNames"));

                QJsonArray personNew;
                if(req->isPerson)
                {
                    obj.insert("PersonalDocuments", i.toObject().value("PersonalDocuments"));
                }else
                {
                    QJsonArray person;
                    for(auto i : documentsPersonName)
                    {
                        QJsonObject value
                        {
                            {"DocumentsName", i},
                            {"DocumentsConfirm", false},
                            {"DocumentsFileName", ""}
                        };
                        person.push_back(value);
                    }
                    obj.insert("PersonalDocuments", person);
                    auto personOld = i.toObject().value("PersonalDocuments").toArray();
                    for(auto j : personOld)
                    {
                        QFile::remove("C:/Qt/project/Server/data/pics/" + j.toObject().value("DocumentsFileName").toString());
                    }
                }
                correct.push_back(obj);
            }else
            {
                correct.push_back(i);
            }
        }
        emit transmitReq(req);
        QJsonObject all
        {
            {"User", correct}
        };
        QJsonDocument newDoc(all);
        data.open(QIODevice::WriteOnly | QIODevice::Text);
        data.write(newDoc.toJson());
        data.close();
    }
}
void ServerNet::transmit(IReq* req)
{
    qDebug() << "Server: transmiting req: " << req->reqName << "to user: "<< req->receiverName;
    transmiter->transmit(req);
}
void ServerNet::transmit(IMsg* msg)
{
    qDebug() << "Server: transmiting req: " << msg->msgName << "to admin";
    transmiter->transmit(msg);
}
