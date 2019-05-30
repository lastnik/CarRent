#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "login.h"
#include "loginmsg.h"
#include "clientnet.h"
#include "core.h"
#include <memory>
#include <QEventLoop>
#include <QTimer>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    unique_ptr<Login>     log  = std::make_unique<Login>();
    unique_ptr<ClientNet> net  = std::make_unique<ClientNet>();
    unique_ptr<Core>      core = std::make_unique<Core>();

    QObject::connect(log.get(), SIGNAL(tryLogin(IMsg*)), net.get(), SLOT(transmit(IMsg*)));
    QObject::connect(net.get(), SIGNAL(receive(IReq*)),  core.get(), SLOT(receiveReq(IReq*)));
    QObject::connect(net.get(), SIGNAL(receive(IMsg*)),  core.get(), SLOT(receiveMsg(IMsg*)));
    QObject::connect(core.get(), SIGNAL(receive(IReq*)),  log.get(), SLOT(receive(IReq*)));
    QObject::connect(log.get(), SIGNAL(resultLogin(LoginReq*)), core.get(), SLOT(start(LoginReq*)));

    QObject::connect(core.get(), SIGNAL(transmitMsgSaver(IMsg*)),  net.get(), SLOT(transmitMsgSaver(IMsg*)));
    QObject::connect(core.get(), SIGNAL(transmitReq(IReq*)),  net.get(), SLOT(transmit(IReq*)));
    //application login
    const QUrl urlLogin(QStringLiteral("qrc:/LoginPage.qml"));
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("login", log.get());
    engine.load(urlLogin);

    context = engine.rootContext();

    context->setContextProperty("core", core.get());

    engine.load(url);

    QObject* root = engine.rootObjects()[0];
    log->setRoot(root);

    QObject::connect(root->findChild<QObject*>("tryLogin"), SIGNAL(clicked()),log.get(), SLOT(login()));
    root = engine.rootObjects()[1];
    core->setRoot(root);
    root->setProperty("visible", false);

    QObject::connect(root, SIGNAL(clickedMe(int)), core.get(), SLOT(event(int)));
    QObject::connect(root, SIGNAL(sendResponce(int,int,int)), core.get(), SLOT(sendResponce(int, int, int)));
    LoginMsg msg;
    log->check(msg);
    auto ret = app.exec();
    net->stop();
    core->save();
    QEventLoop loop;
    QTimer::singleShot(5000, &loop, SLOT(quit()));
    loop.exec();
    return ret;
}
