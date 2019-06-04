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
QString wayData = QString(PATH) + "/data";

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

    msgNum.push_back("RegistrationCarMsg");
    converterMsg["RegistrationCarMsg"] = toRegistrationCarMsgStruct;

    msgNum.push_back("CarInfoMsg");
    converterMsg["CarInfoMsg"] = toCarInfoMsgStruct;

    //registration req
    reqNum.push_back("RegistrationReq");
    converterReq["RegistrationReq"] = toRegistrationReqStruct;

    reqNum.push_back("RegistrationCarReq");
    converterReq["RegistrationCarReq"] = toRegistrationCarReqStruct;


    documentsPersonName.push_back("Passport");
    documentsPersonName.push_back("Driver Licence");

    documentsCarName.push_back("Сertificate");
    documentsCarName.push_back("PTS");
    documentsCarName.push_back("OSAGO");
    documentsCarName.push_back("Photo of car");
    QTimer::singleShot(1000, this, SLOT(receive()));
}




void ServerNet::receive()
{
    qDebug() << "Server: Start Receiving messages";
    //ADMIN
    IMsg* msg = receiver->receiveAdmin("LoginMsg",converterMsg.at("LoginMsg"));
    if(msg != nullptr)
    {
        qDebug() << "Server: Receive msg - " << "LoginMsg";
        emit receiveAdmin(msg);
    }
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
    if(typeid (*msg).name() == typeid (RegistrationCarMsg).name())
    {
        schedulerReq(reinterpret_cast<RegistrationCarMsg*>(msg));
        return;
    }
    if(typeid (*msg).name() == typeid (CarInfoMsg).name())
    {
        schedulerReq(reinterpret_cast<CarInfoMsg*>(msg));
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
    if(typeid (*req).name() == typeid (RegistrationCarReq).name())
    {
        schedulerReq(reinterpret_cast<RegistrationCarReq*>(req));
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
        obj.insert("HasCars", false);
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
                req->isPerson = i.toObject().value("ConfirmPerson").toBool();
                req->hasCars  = i.toObject().value("HasCars").toBool();
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
        QFile::copy(QString(PATH) + "/msg/" + i.second, QString(PATH) + "/data/pics/" + i.second);
        QFile::remove(QString(PATH) + "/msg/" + i.second);
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
                obj.insert("ConfirmPerson", i.toObject().value("ConfirmPerson"));
                obj.insert("HasCars", i.toObject().value("HasCars"));
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
                obj.insert("ConfirmPerson", req->isPerson);
                obj.insert("HasCars", i.toObject().value("HasCars"));
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
                        QFile::remove(QString(PATH) + "/data/pics/" + j.toObject().value("DocumentsFileName").toString());
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
void ServerNet::schedulerReq(RegistrationCarMsg* msg)
{
    for(auto i : msg->documents)
    {
        QFile::copy(QString(PATH) + "/msg/" + i.second, QString(PATH) + "/data/pics/" + i.second);
        QFile::remove(QString(PATH) + "/msg/" + i.second);
    }
    QFile data(wayData + ("/" + QString("Cars") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = data.readAll();
        data.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("Car").toArray();
        auto carName = msg->carBrend + " " + msg->carModel + " " + msg->carNumber;
        QJsonArray correct;
        for(auto i : array)
        {

            if(i.toObject().value("Login").toString() == msg->login && i.toObject().value("CarName").toString() == carName)
            {
                qDebug() << "Server: found in DataBase car with name: " << carName << " for user: "<< msg->login;
                return;
            }else
            {
                correct.push_back(i);
            }
        }
        qDebug() << "Server: create new cell in DataBase for car: " << carName << " of user: " << msg->login;
        QJsonArray arr;
        for(auto i : msg->documents)
        {
            QJsonObject obj
            {
                {"DocumentsName", i.first},
                {"DocumentsFileName", i.second},
                {"DocumentsConfirm", false}
            };
            arr.push_back(obj);
        }
        QJsonObject obj
        {
            {"Login",     msg->login},
            {"CarBrend",  msg->carBrend},
            {"CarModel",  msg->carModel},
            {"CarColor",  msg->carColor},
            {"CarNumber", msg->carNumber},
            {"CarName",   msg->carBrend + " " + msg->carModel + " " + msg->carNumber},
            {"Year",      msg->year},
            {"State",     "none"},
            {"ConfirmCar",false},
            {"Documents", arr},
        };
        correct.push_back(obj);
        emit transmitMsg(msg);
        QJsonObject all
        {
            {"Car", correct}
        };
        QJsonDocument newDoc(all);
        data.open(QIODevice::WriteOnly | QIODevice::Text);
        data.write(newDoc.toJson());
        data.close();
    }
}
void ServerNet::schedulerReq(RegistrationCarReq* req)
{
    bool all = true;
    QFile data(wayData + ("/" + QString("Cars") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = data.readAll();
        data.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("Car").toArray();
        QJsonArray correct;
        for(auto i : array)
        {

            if(i.toObject().value("Login").toString() == req->login
                    && i.toObject().value("CarName").toString() == req->carName)
            {
                if(req->isCar)
                {
                    QJsonArray arr = i.toObject().value("Documents").toArray();
                    QJsonArray arrnew;
                    if(arr.size() == documentsCarName.size())
                    {
                        for(size_t j = 0; j < arr.size(); j++)
                        {
                            if(arr[j].toObject().value("DocumentsName").toString() != documentsCarName[j])
                            {
                                all = false;
                            }else
                            {
                                QJsonObject obj
                                {
                                    {"DocumentsName", arr[j].toObject().value("DocumentsName").toString()},
                                    {"DocumentsFileName", arr[j].toObject().value("DocumentsFileName").toString()},
                                    {"DocumentsConfirm", true}
                                };
                                arrnew.push_back(obj);
                            }
                        }
                        if(all)
                        {
                            qDebug() << "Server: correct cell in DataBase for car: " << req->carName << " of user: " << req->login;
                            QJsonObject obj
                            {
                                {"Login",      i.toObject().value("Login").toString()},
                                {"CarBrend",   i.toObject().value("CarBrend").toString()},
                                {"CarModel",   i.toObject().value("CarModel").toString()},
                                {"CarColor",   i.toObject().value("CarColor").toString()},
                                {"CarNumber",  i.toObject().value("CarNumber").toString()},
                                {"CarName",    i.toObject().value("CarName").toString()},
                                {"Year",       i.toObject().value("Year").toInt()},
                                {"State",      i.toObject().value("State").toString()},
                                {"ConfirmCar", true},
                                {"Documents",  arrnew},
                            };
                            correct.push_back(obj);
                        }else
                        {
                            qDebug() << "Server: delete cell in DataBase for car: " << req->carName << " of user: " << req->login;
                        }
                    }else
                    {
                        req->isCar = false;
                    }
                }else
                {
                    qDebug() << "Server: delete cell in DataBase for car: " << req->carName << " of user: " << req->login;
                }
            }else
            {
                correct.push_back(i);
            }
        }
        QJsonObject all
        {
            {"Car", correct}
        };
        QJsonDocument newDoc(all);
        data.open(QIODevice::WriteOnly | QIODevice::Text);
        data.write(newDoc.toJson());
        data.close();
    }
    if(req->isCar)
    {
        QFile data1(wayData + ("/" + QString("Access") + ".json"));
        if(data1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            auto val = data1.readAll();
            data1.close();
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
                    obj.insert("ConfirmPerson", i.toObject().value("ConfirmPerson"));
                    obj.insert("HasCars", true);
                    auto arr = i.toObject().value("CarNames").toArray();
                    arr.push_back(req->carName);
                    obj.insert("CarNames", arr);
                    obj.insert("PersonalDocuments", i.toObject().value("PersonalDocuments"));
                    correct.push_back(obj);
                    emit transmitReq(req);
                }else
                {
                    correct.push_back(i);
                }
            }
            QJsonObject all
            {
                {"User", correct}
            };
            QJsonDocument newDoc(all);
            data1.open(QIODevice::WriteOnly | QIODevice::Text);
            data1.write(newDoc.toJson());
            data1.close();
        }
    }
}
void ServerNet::schedulerReq(CarInfoMsg *msg)
{
    qDebug() << "Server: confirm info about car : " << msg->carName << " for user: " << msg->login;
    CarInfoReq* req = new CarInfoReq();
    req->login = msg->login;
    req->carName = msg->carName;
    QFile data(wayData + ("/" + QString("Cars") + ".json"));
    if(data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = data.readAll();
        data.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        auto array =  doc.object().value("Car").toArray();
        QJsonArray correct;
        for(auto i : array)
        {
            if(i.toObject().value("CarName").toString() == req->carName)
            {
                QJsonArray arr = i.toObject().value("Documents").toArray();
                req->carBrend = i.toObject().value("CarBrend").toString();
                req->carModel = i.toObject().value("CarModel").toString();
                req->carColor = i.toObject().value("CarColor").toString();
                req->carOwner = i.toObject().value("Login").toString();
                req->carNumber = i.toObject().value("CarNumber").toString();
                req->year = i.toObject().value("Year").toInt();
                req->isCar = i.toObject().value("ConfirmCar").toBool();
                req->carState = i.toObject().value("State").toString();
                req->receiverName = req->login;
                for(auto j : arr)
                {
                    if(j.toObject().value("DocumentsName").toString() == "Photo of car")
                    {
                        req->documents.push_back(std::make_pair(j.toObject().value("DocumentsName").toString(),
                                                                j.toObject().value("DocumentsFileName").toString()));
                        auto a = QString(PATH) + "/data/pics/" + j.toObject().value("DocumentsFileName").toString();
                        auto b = QString(CLIENTPATH) + "/cache/" + j.toObject().value("DocumentsFileName").toString();
                        QFile::copy(a,b);
                    }
                }
                break;
            }
        }
    }
    emit transmitReq(req);
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
