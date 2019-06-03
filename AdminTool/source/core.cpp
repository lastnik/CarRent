#include "core.h"
#include "clientnet.h"
#include <QVariant>
#include <vector>
#include <utility>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
Core::Core(QObject *parent) : QObject(parent)
{

}

void Core::start(LoginReq* req)
{
    delete req;
    root->setProperty("visible", true);
}
void Core::save()
{
    for(auto i : historyPerson)
    {
        transmitMsgSaver(i);
    }
    for(auto i : historyCar)
    {
        transmitMsgSaver(i);
    }
}
void Core::receiveReq(IReq* req)
{
    if(typeid (*req).name() == typeid (LoginReq).name())
    {
        emit receive(req);
        return;
    }
}

void Core::sendResponce(int indexReq, int totalReq, int value)
{
    if(total[totalReq].first == "Person registration")
    {
        RegistrationMsg* msg = historyPerson[total[totalReq].second];
        if(msg == historyPerson[indexReq])
        {
            RegistrationReq* req = new RegistrationReq();
            req->login = msg->login;
            int a = msg->documents.size();
            emit clearDoc();
            for(auto i : msg->documents)
            {
                emit addDoc(i.first, "");
            }
            emit clearDoc();
            if(((1 << a) - 1 ) == value)
            {
                req->isPerson = true;
            }else
            {
                req->isPerson = false;
            }
            emit transmitReq(req);
            historyPerson.erase(historyPerson.begin() + indexReq);
            total.erase(total.begin() + totalReq);
            emit erase(totalReq);
        }
    }else
    {
        //car
        RegistrationCarMsg* msg = historyCar[total[totalReq].second];
        if(msg == historyCar[indexReq])
        {
            RegistrationCarReq* req = new RegistrationCarReq();
            req->login = msg->login;
            int a = msg->documents.size();
            emit clearDoc();
            for(auto i : msg->documents)
            {
                emit addDoc(i.first, "");
            }
            emit clearDoc();
            req->carName = msg->carBrend + " " + msg->carModel + " " + msg->carNumber;
            if(a <= 0)
            {
                req->isCar = false;
            }else
            {
                if(((1 << a) - 1 ) == value)
                {
                    req->isCar = true;
                }else
                {
                    req->isCar = false;
                }
            }
            emit transmitReq(req);
            historyCar.erase(historyCar.begin() + indexReq);
            total.erase(total.begin() + totalReq);
            emit erase(totalReq);
        }
    }
}

void Core::schedulerReq(RegistrationMsg* msg)
{
    historyPerson.push_back(msg);
    emit add(msg->login, "Person registration");
    total.push_back(std::make_pair("Person registration", historyPerson.size() - 1));
}

void Core::schedulerReq(RegistrationCarMsg* msg)
{
    historyCar.push_back(msg);
    emit add(msg->login, "Car registration");
    total.push_back(std::make_pair("Car registration", historyCar.size() - 1));
}
void Core::event(int index)
{
    if(total[index].first == "Person registration")
    {
        //person
        RegistrationMsg* msg = historyPerson[total[index].second];
        root->findChild<QObject*>("personRegistration")->setProperty("bitmap", 0 );
        root->findChild<QObject*>("personRegistration")->setProperty("indexReq", total[index].second);
        root->findChild<QObject*>("personRegistration")->setProperty("totalReq", index);
        root->findChild<QObject*>("personRegistration")->setProperty("visible", true);
        emit clearDoc();
        for(auto i : msg->documents)
        {
            emit addDoc(i.first, QString(SERVERPATH) + "/Server/data/pics/" + i.second);
        }
    }else
    {
        //car
        if(total[index].first == "Car registration"){
            RegistrationCarMsg* msg = historyCar[total[index].second];
            root->findChild<QObject*>("carRegistration")->setProperty("bitmap", 0 );
            root->findChild<QObject*>("carRegistration")->setProperty("indexReq", total[index].second);
            root->findChild<QObject*>("carRegistration")->setProperty("totalReq", index);
            root->findChild<QObject*>("carRegistration")->setProperty("visible", true);
            emit clearDoc();
            root->findChild<QObject*>("carRegistration")->setProperty("brend",  msg->carBrend);
            root->findChild<QObject*>("carRegistration")->setProperty("model",  msg->carModel);
            root->findChild<QObject*>("carRegistration")->setProperty("color",  msg->carColor);
            root->findChild<QObject*>("carRegistration")->setProperty("number", msg->carNumber);
            root->findChild<QObject*>("carRegistration")->setProperty("year",   msg->year);
            for(auto i : msg->documents)
            {
                emit addDoc(i.first, QString(SERVERPATH) + "/Server/data/pics/" + i.second);
            }
        }
    }
}
void Core::receiveMsg(IMsg* msg)
{
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
}

void Core::setRoot(QObject *_root)
{
    root = _root;
}


