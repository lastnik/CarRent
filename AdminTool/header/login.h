#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QFile>
#include <QString>
#include "imsg.h"
#include "loginmsg.h"
#include <QResource>
class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login();
    void check(LoginMsg& msg);
    void setRoot(QObject*);
public slots:
    void receive(IReq*);
    void login();
    void registration();
    void timing();
signals:
    void tryLogin(IMsg* msg);
    void resultLogin(LoginReq*);
    void logFail();
    void loginPage();
    void watingPage();
    void finishLogin();
private:
    QFile     file;
    QObject*  root;
    LoginReq* reqCor = nullptr;
    QResource resource;
};

#endif // LOGIN_H
