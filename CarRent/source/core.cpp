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
    login = req->login;
    ClientNet::setLogin(login);
    delete req;
    root->setProperty("visible", true);
    accessInfo();
}

void Core::accessInfo()
{
    AccessMsg* msg = new AccessMsg();
    msg->login = login;
    emit transmitMsg(msg);
}

void Core::receiveReq(IReq* req)
{
    if(typeid (*req).name() == typeid (LoginReq).name())
    {
        emit receive(req);
        return;
    }
    if(typeid (*req).name() == typeid (AccessReq).name())
    {
        scheduler(reinterpret_cast<AccessReq*>(req));
        return;
    }
    if(typeid (*req).name() == typeid (RegistrationReq).name())
    {
        scheduler(reinterpret_cast<RegistrationReq*>(req));
        return;
    }
}

void Core::scheduler(AccessReq* req)
{
    QStringList list;
    emit clear();
    int id = 0;
    for(auto i : req->documents)
    {
        if(!i.second)
        {
            emit add(id, i.first, false);
            list.push_back(i.first);
            id++;
        }
    }
    emit setDocName(list);
    if(list.size() == 0 && req->isPerson == false)
    {
        root->findChild<QObject*>("registrationPerson")->setProperty("visible", false);
        emit waitingConfirm();
    }else
    {
        if(list.size() != 0 && req->isPerson == false)
        {
            root->findChild<QObject*>("registrationPerson")->setProperty("visible", true);
        }else
        {
            if(list.size() != 0 && req->isPerson == true)
            {
                root->findChild<QObject*>("registrationPerson")->setProperty("visible", false);
            }
        }
    }
    root->findChild<QObject*>("busyIndicatorMain")->setProperty("visible", false);
    root->findChild<QObject*>("stackView")->setProperty("visible", true);
    delete req;
}

void Core::scheduler(RegistrationReq* req)
{
    if(req->isPerson)
    {
        root->findChild<QObject*>("successReg3")->setProperty("text", "Now you have access to car rentals.");
    }else
    {
        root->findChild<QObject*>("successReg3")->setProperty("text", "Sorry, you documents is incorrect.");
    }
    root->findChild<QObject*>("successReg")->setProperty("visible", true);
    delete req;
    accessInfo();
}


void Core::setRoot(QObject *_root)
{
    root = _root;
}

void Core::confirmDocs(std::vector<std::pair<QString, QString>> docs)
{
    RegistrationMsg* msg = new RegistrationMsg();
    msg->login = login;
    for(auto i : docs)
    {
        QFileInfo info(i.second);
        QFile::copy(i.second, QString(PATH) + "/../Server/msg/" + i.first + msg->login + "." + info.suffix());
        msg->documents.push_back(std::make_pair(i.first, i.first + msg->login + "." + info.suffix()));
    }
    emit transmitMsg(msg);
    emit waitingConfirm();
    root->findChild<QObject*>("registrationPerson")->setProperty("visible",false);
}
