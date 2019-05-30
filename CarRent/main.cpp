#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calendar.h"
#include "login.h"
#include "loginmsg.h"
#include "clientnet.h"
#include "documentsmodel.h"
#include "core.h"
#include <memory>
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

    QStringList docPerson = { "Passport", "DriverLiceince"};
    unique_ptr<DocumentsModel> person = std::make_unique<DocumentsModel>(docPerson);

    QObject::connect(log.get(), SIGNAL(tryLogin(IMsg*)), net.get(), SLOT(transmit(IMsg*)));
    QObject::connect(net.get(), SIGNAL(receive(IReq*)),  core.get(), SLOT(receiveReq(IReq*)));
    QObject::connect(core.get(), SIGNAL(receive(IReq*)),  log.get(), SLOT(receive(IReq*)));
    QObject::connect(log.get(), SIGNAL(resultLogin(LoginReq*)), core.get(), SLOT(start(LoginReq*)));
    QObject::connect(core.get(), SIGNAL(setDocName(QStringList)), person.get(), SLOT(setDocName(QStringList)));
    QObject::connect( person.get(), SIGNAL(confirmDocs(std::vector<std::pair<QString, QString>>))
                    , core.get(), SLOT(confirmDocs(std::vector<std::pair<QString, QString>>)));
    QObject::connect(core.get(), SIGNAL(transmitMsg(IMsg*)), net.get(), SLOT(transmit(IMsg*)));
    //application login
    const QUrl urlLogin(QStringLiteral("qrc:/LoginPage.qml"));
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("login", log.get());
    engine.load(urlLogin);

    context = engine.rootContext();
    unique_ptr<SenderCalendar> senderCalendar = std::make_unique<SenderCalendar>(nullptr);
    context->setContextProperty("calendar", senderCalendar.get());
    context->setContextProperty("personModel", person.get());
    context->setContextProperty("core", core.get());

    engine.load(url);

    QObject* root = engine.rootObjects()[0];
    log->setRoot(root);

    QObject::connect(root->findChild<QObject*>("tryLogin"), SIGNAL(clicked()),log.get(), SLOT(login()));
    QObject::connect(root->findChild<QObject*>("registration"), SIGNAL(clicked()),log.get(), SLOT(registration()));
    root = engine.rootObjects()[1];
    core->setRoot(root);
    root->setProperty("visible", false);

    LoginMsg msg;
    log->check(msg);




    //main application

    unique_ptr<Calendar> calendar = std::make_unique<Calendar>(root);

    QObject::connect(root->findChild<QObject*>("rightArrow"), SIGNAL(changeMonth(QDateTime)), calendar.get(), SLOT(incMonth(QDateTime)));
    QObject::connect(root->findChild<QObject*>("leftArrow"), SIGNAL(changeMonth(QDateTime)), calendar.get(), SLOT(decMonth(QDateTime)));
    QObject::connect(root->findChild<QObject*>("grid"), SIGNAL(changeDate(QDateTime)), senderCalendar.get(), SLOT(changeDate(QDateTime)));

    QObject::connect(root, SIGNAL(attachImage(int, QString)), person.get(), SLOT(setDocFile(int, QString)));
    QObject::connect(root, SIGNAL(confirmPerson()), person.get(), SLOT(confirm()));
    return app.exec();
}
