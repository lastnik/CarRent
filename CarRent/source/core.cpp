#include "core.h"
#include "clientnet.h"
#include <QVariant>
#include <vector>
#include <utility>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDate>
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
    if(typeid (*req).name() == typeid (RegistrationCarReq).name())
    {
        scheduler(reinterpret_cast<RegistrationCarReq*>(req));
        return;
    }
    if(typeid (*req).name() == typeid (CarInfoReq).name())
    {
        scheduler(reinterpret_cast<CarInfoReq*>(req));
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
            if(list.size() == 0 && req->isPerson == true)
            {
                root->findChild<QObject*>("registrationPerson")->setProperty("visible", false);
                root->findChild<QObject*>("myCars")->setProperty("visible", true);
                if(req->hasCars)
                {
                    emit clearCar();
                    for(auto i : req->carsNames)
                    {
                        transmitCarInfoMsg(i);
                    }
                }
            }
        }
    }
    root->findChild<QObject*>("busyIndicatorMain")->setProperty("visible", false);
    root->findChild<QObject*>("stackView")->setProperty("visible", true);
    delete req;
}

void Core::transmitCarInfoMsg(QString carsName)
{
    CarInfoMsg* msg = new CarInfoMsg();
    msg->login = login;
    msg->carName = carsName;
    emit transmitMsg(msg);
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

void Core::scheduler(RegistrationCarReq* req)
{
    if(req->isCar)
    {
        root->findChild<QObject*>("successReg3")->setProperty("text", "Now you have access to car rent.");
    }else
    {
        root->findChild<QObject*>("successReg3")->setProperty("text", "Sorry, you documents is incorrect.");
    }
    root->findChild<QObject*>("successReg")->setProperty("visible", true);
    delete req;
    accessInfo();
}

void Core::scheduler(CarInfoReq *req)
{
    //TODO: add a few functional
    CarParam param;
    param.isLast     = false;
    param.carName    = req->carName;
    param.carPics    = req->documents[0].second;
    param.carOwner   = req->carOwner;
    param.carBrend   = req->carBrend;
    param.carModel   = req->carModel;
    param.carColor   = req->carColor;
    param.carNumber  = req->carNumber;
    param.carConfirm = req->isCar;
    param.year       = req->year;
    param.carState   = req->carState;
    delete req;
    emit addCar(param);
}

void Core::setRoot(QObject *_root)
{
    root = _root;
}

void Core::confirmDocs(std::vector<std::pair<QString, QString>> docs)
{
    if(docs.size() == 2)
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
    }else
    {
        auto brend = root->findChild<QObject*>("lineCarBrend")->property("text").toString();
        auto model = root->findChild<QObject*>("lineCarModel")->property("text").toString();
        auto color = root->findChild<QObject*>("lineCarColor")->property("text").toString();
        auto number= root->findChild<QObject*>("lineCarNumber")->property("text").toString();
        auto year  = QDate().currentDate().year() - 100 + root->findChild<QObject*>("tumblerCarYear")->property("currentIndex").toInt();
        bool _error = false;
        if(brend.size() == 0)
        {
            emit error(0);
            _error = true;
        }

        if(model.size() == 0)
        {
            emit error(1);
            _error = true;
        }

        if(color.size() == 0)
        {
            emit error(2);
            _error = true;
        }

        if(number.size() == 0)
        {
            emit error(3);
            _error = true;
        }
        if(_error) return;
        RegistrationCarMsg* msg = new RegistrationCarMsg();
        msg->login = login;
        msg->carBrend = brend;
        msg->carModel = model;
        msg->carColor = color;
        msg->carNumber = number;
        msg->year = year;
        for(auto i : docs)
        {
            QFileInfo info(i.second);
            QFile::copy(i.second, QString(PATH) + "/../Server/msg/" + i.first + " " + msg->carBrend + " " + msg->carModel + " " + msg->carNumber + "." + info.suffix());
            msg->documents.push_back(std::make_pair(i.first, i.first + " " + msg->carBrend + " " + msg->carModel + " " + msg->carNumber + "." + info.suffix()));
        }

        CarParam param;
        param.carName = msg->carBrend + " " + msg->carModel + " " + msg->carNumber;
        param.carPics = msg->documents.back().second;
        param.carNumber = msg->carNumber;
        param.carOwner  = msg->login;
        param.carBrend  = msg->carBrend;
        param.carModel  = msg->carModel;
        param.carColor  = msg->carColor;
        param.carConfirm  = false;
        param.isLast  = false;
        param.carState  = "none";
        param.year    = msg->year;
        emit addCar(param);
        emit transmitMsg(msg);
        emit waitingConfirm();

        emit pop();
    }
}
void Core::rentalMsg(QString _login, QString name, double cost)
{
    if(_login != login) return;
    ConfirmRentalMsg* msg = new ConfirmRentalMsg();
    msg->login = login;
    msg->cost = cost;
    msg->carName = name;
    QString format = "mm-dd-yyyy";
    msg->from = root->findChild<QObject*>("from")->property("fromDate").toDate().toString(format);
    msg->to   = root->findChild<QObject*>("to")->property("toDate").toDate().toString(format);
    transmitMsg(msg);
}
