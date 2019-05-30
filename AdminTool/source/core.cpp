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
    for(auto i : history)
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
        RegistrationMsg* msg = history[total[totalReq].second];
        if(msg == history[indexReq])
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
            history.erase(history.begin() + indexReq);
            total.erase(total.begin() + totalReq);
            emit erase(totalReq);
        }
    }else
    {
        //car
    }
}

void Core::schedulerReq(RegistrationMsg* msg)
{
    history.push_back(msg);
    emit add(msg->login, "Person registration");
    total.push_back(std::make_pair("Person registration", history.size() - 1));
}
void Core::event(int index)
{

    if(total[index].first == "Person registration")
    {
        //person
        RegistrationMsg* msg = history[total[index].second];
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
    }
}
void Core::receiveMsg(IMsg* msg)
{
    if(typeid (*msg).name() == typeid (RegistrationMsg).name())
    {
        schedulerReq(reinterpret_cast<RegistrationMsg*>(msg));
        return;
    }
}

void Core::setRoot(QObject *_root)
{
    root = _root;
}


