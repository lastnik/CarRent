#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calendar.h"
#include "login.h"
#include "loginmsg.h"
#include "clientnet.h"
#include "documentsmodel.h"
#include "rentaladmodel.h"
#include "chatlistmodel.h"
#include "chatmodel.h"
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
    QStringList docCar =    { "Сertificate", "PTS", "OSAGO", "Photo of car"};
    unique_ptr<DocumentsModel> person = std::make_unique<DocumentsModel>(docPerson);
    unique_ptr<DocumentsModel> car = std::make_unique<DocumentsModel>(docCar);
    unique_ptr<CarModel>       cars   = std::make_unique<CarModel>();

    unique_ptr<RentalAdModel>  rentals = std::make_unique<RentalAdModel>();
    unique_ptr<ChatModel> chat = std::make_unique<ChatModel>();
    unique_ptr<ChatListModel> listchat = std::make_unique<ChatListModel>();



    QObject::connect(log.get(), SIGNAL(tryLogin(IMsg*)), net.get(), SLOT(transmit(IMsg*)));
    QObject::connect(net.get(), SIGNAL(receive(IReq*)),  core.get(), SLOT(receiveReq(IReq*)));
    QObject::connect(core.get(), SIGNAL(receive(IReq*)),  log.get(), SLOT(receive(IReq*)));
    QObject::connect(log.get(), SIGNAL(resultLogin(LoginReq*)), core.get(), SLOT(start(LoginReq*)));
    QObject::connect(core.get(), SIGNAL(setDocName(QStringList)), person.get(), SLOT(setDocName(QStringList)));
    QObject::connect( person.get(), SIGNAL(confirmDocs(std::vector<std::pair<QString, QString>>))
                    , core.get(), SLOT(confirmDocs(std::vector<std::pair<QString, QString>>)));

    QObject::connect( car.get(), SIGNAL(confirmDocs(std::vector<std::pair<QString, QString>>))
                    , core.get(), SLOT(confirmDocs(std::vector<std::pair<QString, QString>>)));

    QObject::connect(core.get(), SIGNAL(setRentalAd(std::vector<RentalAd>)), rentals.get(), SLOT(setParams(std::vector<RentalAd>)));

    QObject::connect( core.get(), SIGNAL(addCar(CarParam)), cars.get(), SLOT(addParam(CarParam)));
    QObject::connect( core.get(), SIGNAL(addCarRentalAd(CarRentalAd)), cars.get(), SLOT(addCarRentalAd(CarRentalAd)));
    QObject::connect( core.get(), SIGNAL(clearCar()), cars.get(), SLOT(clear()));
    QObject::connect( cars.get(), SIGNAL(waitingConfirm()), core.get(), SIGNAL(waitingConfirm()));
    QObject::connect( core.get(), SIGNAL(transmitMsg(IMsg*)), net.get(), SLOT(transmit(IMsg*)));
    QObject::connect( cars.get(), SIGNAL(rentalMsg(QString, QString, double)), core.get(), SLOT(rentalMsg(QString, QString, double)));
    QObject::connect( rentals.get(), SIGNAL(see(QString)), core.get(), SLOT(see(QString)));
    QObject::connect( cars.get(), SIGNAL(chatUpdate(QString, QString)), core.get(), SLOT(chatUpdateList(QString, QString)));

    QObject::connect( listchat.get(), SIGNAL(addMsg(Message)), chat.get(), SLOT(addMsg(Message)));
    QObject::connect( listchat.get(), SIGNAL(pushMsg(Message, QString)), core.get(), SLOT(pushMsg(Message, QString)));
    QObject::connect( core.get(), SIGNAL(loadMsg(Message)), listchat.get(), SLOT(loadMsg(Message)));
    QObject::connect( core.get(), SIGNAL(addChatInfo(QString,QString)), listchat.get(), SLOT(addChatInfo(QString,QString)));
    QObject::connect( core.get(), SIGNAL(zeroChat()), listchat.get(), SLOT(setFirst()));
    QObject::connect( core.get(), SIGNAL(clearListChat()), listchat.get(), SLOT(clear()));
    QObject::connect( core.get(), SIGNAL(setChat(QString,QString,std::vector<Message>)), listchat.get(), SLOT(setChat(QString,QString,std::vector<Message>)));
    QObject::connect( listchat.get(), SIGNAL(clearChat()), chat.get(), SLOT(clear()));
    QObject::connect( listchat.get(), SIGNAL(setMsgs(std::vector<Message>)), chat.get(), SLOT(setMsgs(std::vector<Message>)));


    //application login
    const QUrl urlLogin(QStringLiteral("qrc:/LoginPage.qml"));
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("login", log.get());
    engine.load(urlLogin);

    context = engine.rootContext();
    unique_ptr<SenderCalendar> senderCalendar = std::make_unique<SenderCalendar>(nullptr);
    context->setContextProperty("calendar", senderCalendar.get());
    context->setContextProperty("personModel", person.get());
    context->setContextProperty("carModel", cars.get());
    context->setContextProperty("carDocModel", car.get());
    context->setContextProperty("core", core.get());
    context->setContextProperty("rentalModel", rentals.get());
    context->setContextProperty("chat", chat.get());
    context->setContextProperty("chatList", listchat.get());

    engine.load(url);

    QObject* root = engine.rootObjects()[0];
    log->setRoot(root);

    QObject::connect(root->findChild<QObject*>("tryLogin"), SIGNAL(clicked()),log.get(), SLOT(login()));
    QObject::connect(root->findChild<QObject*>("registration"), SIGNAL(clicked()),log.get(), SLOT(registration()));
    root = engine.rootObjects()[1];
    core->setRoot(root);
    cars->setRoot(root);
    root->setProperty("visible", false);

    LoginMsg msg;
    log->check(msg);




    //main application

    unique_ptr<Calendar> calendar = std::make_unique<Calendar>(root);

    QObject::connect(root->findChild<QObject*>("rightArrow"), SIGNAL(changeMonth(QDateTime)), calendar.get(), SLOT(incMonth(QDateTime)));
    QObject::connect(root->findChild<QObject*>("leftArrow"), SIGNAL(changeMonth(QDateTime)), calendar.get(), SLOT(decMonth(QDateTime)));
    QObject::connect(root->findChild<QObject*>("grid"), SIGNAL(changeDate(QDateTime)), senderCalendar.get(), SLOT(changeDate(QDateTime)));

    QObject::connect(root, SIGNAL(attachImage(int, QString)), person.get(), SLOT(setDocFile(int, QString)));
    QObject::connect(root, SIGNAL(attachImageCar(int, QString)), car.get(), SLOT(setDocFile(int, QString)));
    QObject::connect(root, SIGNAL(confirmPerson()), person.get(), SLOT(confirm()));
    QObject::connect(root, SIGNAL(confirmCar()), car.get(), SLOT(confirmCar()));
    QObject::connect(root, SIGNAL(confirmRental()), cars.get(), SLOT(confirmRental()));
    QObject::connect(root, SIGNAL(carView(int)), cars.get(), SLOT(carView(int)));
    QObject::connect(root, SIGNAL(updateData()), core.get(), SLOT(rentalListInfo()));
    QObject::connect(root, SIGNAL(rentalView(int)), rentals.get(), SLOT(rentalView(int)));
    QObject::connect(root, SIGNAL(rentalRespond(QString, QString)), core.get(), SLOT(rentalRespond(QString, QString)));
    QObject::connect(root, SIGNAL(atemptRespond(bool)), core.get(), SLOT(atemptRespond(bool)));
    QObject::connect(root, SIGNAL(chatPush(QString, QString)), listchat.get(), SLOT(confirmMsg(QString, QString)));
    QObject::connect(root, SIGNAL(setChatN(int)), listchat.get(), SLOT(setActiveChat(int)));
    return app.exec();
}
