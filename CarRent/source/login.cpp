#include "login.h"
#include "clientnet.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QTimer>
#include <QFileInfo>
Login::Login()
    : file(":/cache/cache/login.json")
    , resource(":/cache/cache/login.json")
{
    connect(this, SIGNAL(resultLogin(LoginReq*)), this, SIGNAL(finishLogin()));
}

void Login::check(LoginMsg& msg)
{
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        QString Login = doc.object().value("Login").toString();
        QString Password = doc.object().value("Password").toString();
        if(Login.size() > 0 && Password.size() > 0)
        {
            emit loginPage();
            msg.isUser = true;
            msg.login = Login;
            msg.password = Password;
            emit tryLogin(&msg);
            ClientNet::setLogin(msg.login);
            QTimer::singleShot(1000000, this, SIGNAL(timing()));
            emit watingPage();
        }else
        {
            msg.isUser = false;
            emit logFail();
        }
    }else
    {
        msg.isUser = false;
        emit logFail();
    }
}

void Login::receive(IReq* req)
{
    auto _req = reinterpret_cast<LoginReq*>(req);
    if(_req->isCorrect)
    {
        ClientNet::setLogin(_req->login);
        reqCor = _req;
        /*
        auto filepath = QFileInfo(file).absoluteFilePath();
        auto filename = resource.fileName();
        resource.unregisterResource(filename);
        file.setFileName(filepath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonObject obj
        {
            {"Login",     reqCor->login},
            {"Password",  reqCor->password},
        };
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
        //QResource::registerResource(filename);
        resource.registerResource(filepath);
        */
        emit resultLogin(_req);
    }else
    {
        root->findChild<QObject*>("errorCode")->setProperty("visible",true);
        emit logFail();
        emit loginPage();
    }
}
void Login::login()
{
    QString login = (root->findChild<QObject*>("logName")->property("text")).toString();
    QString password = (root->findChild<QObject*>("password")->property("text")).toString();
    if(login.size() > 0 && password.size() > 0)
    {
        LoginMsg* msg = new LoginMsg();
        msg->login=login;
        msg->password = password;
        msg->isUser = true;
        ClientNet::setLogin(msg->login);
        emit tryLogin(msg);
        QTimer::singleShot(5000, this, SLOT(timing()));
        emit watingPage();
    }else
    {
        emit loginPage();
    }
}
void Login::registration()
{
    QString login = (root->findChild<QObject*>("logName")->property("text")).toString();
    QString password = (root->findChild<QObject*>("password")->property("text")).toString();
    if(login.size() > 0 && password.size() > 0)
    {
        LoginMsg* msg = new LoginMsg();
        msg->login=login;
        msg->password = password;
        msg->isUser = false;
        ClientNet::setLogin(msg->login);
        emit tryLogin(msg);
        QTimer::singleShot(5000, this, SLOT(timing()));
        emit watingPage();
    }else
    {
        emit loginPage();
    }
}

void Login::setRoot(QObject * _root)
{
    root = _root;
}

void Login::timing()
{
    if(reqCor == nullptr)
    {
        root->findChild<QObject*>("errorCode")->setProperty("visible",true);
        emit logFail();
        emit loginPage();
    }
}
