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
    rentalListInfo();
}

void Core::rentalListInfo()
{
    RentalListInfoMsg* msg = new RentalListInfoMsg();
    msg->login = login;
    QString format = "MM-dd-yyyy";
    msg->from = root->findChild<QObject*>("from")->property("fromDate").toDate().toString(format);
    msg->to   = root->findChild<QObject*>("to")->property("toDate").toDate().toString(format);
    emit transmitMsg(msg);
    root->findChild<QObject*>("rentalLog")->setProperty("visible",false);
    root->findChild<QObject*>("rentalView")->setProperty("visible",false);
    root->findChild<QObject*>("rentalControl")->setProperty("visible",true);
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
    if(typeid (*req).name() == typeid (ConfirmRentalReq).name())
    {
        scheduler(reinterpret_cast<ConfirmRentalReq*>(req));
        return;
    }
    if(typeid (*req).name() == typeid (RentalInfoReq).name())
    {
        scheduler(reinterpret_cast<RentalInfoReq*>(req));
        return;
    }
    if(typeid (*req).name() == typeid (RentalListInfoReq).name())
    {
        scheduler(reinterpret_cast<RentalListInfoReq*>(req));
        return;
    }
    if(typeid (*req).name() == typeid (RentalRespondReq).name())
    {
        scheduler(reinterpret_cast<RentalRespondReq*>(req));
        return;
    }

    if(typeid (*req).name() == typeid (ChatListReq).name())
    {
        scheduler(reinterpret_cast<ChatListReq*>(req));
        return;
    }
    if(typeid (*req).name() == typeid (ChatInfoReq).name())
    {
        scheduler(reinterpret_cast<ChatInfoReq*>(req));
        return;
    }
    if(typeid (*req).name() == typeid (NewMsgChatReq).name())
    {
        scheduler(reinterpret_cast<NewMsgChatReq*>(req));
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
    isPerson = req->isPerson;
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
    RentalInfoMsg* msg1 =  new RentalInfoMsg();
    msg1->login = login;
    msg1->carName = carsName;
    emit transmitMsg(msg1);
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
    if(seeInfoCar){
       seeInfoCar = false;
       root->setProperty("_carOwner",   req->carOwner);
       root->setProperty("_carName",    req->carName);
       root->setProperty("_carBrend",   req->carBrend);
       root->setProperty("_carModel",   req->carModel);
       root->setProperty("_carColor",   req->carColor);
       root->setProperty("_carNumber",  req->carNumber);
       root->setProperty("_carPics",    QString(PATH) + "/cache/" + req->documents[0].second);
       root->setProperty("_carConfirm", true);
       root->setProperty("_login",      req->login);
       root->setProperty("_year",       req->year);
       root->setProperty("_year",       req->year);
       root->setProperty("_buttonVisible", false);
       if(req->carState == "free")
       {
            root->setProperty("_visFrame", true);
            root->setProperty("_visRental", true);
       }else
       {
           if(req->carState == "none")
           {
               root->setProperty("_visFrame", true);
               root->setProperty("_visRental", false);
           }else
           {
               if(req->carState == "rental")
               {
                   root->setProperty("_visFrame", false);
                   root->setProperty("_visRental", true);
                   root->setProperty("_multiplyChatWindow", false);
               }
           }
       }
       if(login != req->carOwner){
           root->setProperty("_visFrame", false);
           root->setProperty("_buttonVisible", true);
           root->setProperty("_multiplyChatWindow", false);
           root->setProperty("_carRentUser", req->carOwner);
           chatReady = true;
       }else
       {
           root->setProperty("_buttonVisible", false);
           root->setProperty("_multiplyChatWindow", true);
       }
       if(!seeInfoRental)
       {
           root->findChild<QObject*>("busyIndicatorMain")->setProperty("visible", false);
           root->findChild<QObject*>("stackView")->setProperty("visible", true);
           emit seeCarPage();
       }
    }
    else
    {
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
        param.login      = login;
        //delete req;
        emit addCar(param);
    }
    delete req;
}
void Core::scheduler(ConfirmRentalReq *req)
{
    transmitCarInfoMsg(req->carName);
    if(req->login == login)
    {
        if(req->result)
        {
            root->findChild<QObject*>("successRegRentals2")->setProperty("text", "for you car " + req->carName + ".");
            root->findChild<QObject*>("successRegRentals")->setProperty("visible", true);
        }
    }
}
void Core::scheduler(RentalInfoReq *req)
{
    if(seeInfoRental)
    {
        seeInfoRental = false;
        root->setProperty("_carCost",     req->cost);
        root->setProperty("_carFrom",     req->from);
        root->setProperty("_carTo",       req->to);
        //if(req->rentUser != "")
        //root->setProperty("_carRentUser", req->rentUser);
        if(!seeInfoCar)
        {
            root->findChild<QObject*>("busyIndicatorMain")->setProperty("visible", false);
            root->findChild<QObject*>("stackView")->setProperty("visible", true);
            emit seeCarPage();
        }
    }else
    {
        CarRentalAd ad;
        if(req->login != login) return;
        ad.carName = req->carName;
        ad.from = req->from;
        ad.to = req->to;
        ad.cost = req->cost;
        emit addCarRentalAd(ad);
    }
    delete req;
}
void Core::scheduler(RentalListInfoReq *req)
{
    std::vector<RentalAd> arr;
    arr.resize(req->infoList.size());
    for(size_t i = 0; i < arr.size(); i++)
    {
        arr[i].carOwner = req->infoList[i]->login;
        arr[i].carName  = req->infoList[i]->carName;
        arr[i].from     = req->infoList[i]->from;
        arr[i].to       = req->infoList[i]->to;
        arr[i].cost     = req->infoList[i]->cost;
    }
    emit setRentalAd(arr);
    if(arr.size() == 0)
    {
        root->findChild<QObject*>("rentalLog")->setProperty("visible", true);
        root->findChild<QObject*>("rentalView")->setProperty("visible",false);
    }else
    {
        root->findChild<QObject*>("rentalLog")->setProperty("visible", false);
        root->findChild<QObject*>("rentalView")->setProperty("visible",true);
    }
    root->findChild<QObject*>("rentalControl")->setProperty("visible",false);

    delete req;
}

void Core::scheduler(RentalRespondReq *_req)
{
    if(reqs != nullptr)
    {
        delete reqs;
        reqs = nullptr;
    }
    reqs = _req;
    if(reqs->login == reqs->carOwner)
    {
        root->findChild<QObject*>("respondeRentals")->setProperty("visible", true);
        root->findChild<QObject*>("respondeRentals1")->setProperty("text", "User " + reqs->rentalUser + " would like to rent");
        root->findChild<QObject*>("respondeRentals2")->setProperty("text", "your car: " + reqs->carName + ". Do you agree with this?");
        root->findChild<QObject*>("respondeRentals1")->setProperty("visible", true);
        root->findChild<QObject*>("respondeRentals2")->setProperty("visible", true);
        root->findChild<QObject*>("respondeRentalsButton1")->setProperty("visible", true);
        root->findChild<QObject*>("respondeRentalsButton2")->setProperty("visible", true);
    }else
    {
        root->findChild<QObject*>("respondeRentals")->setProperty("visible", true);
        root->findChild<QObject*>("respondeRentals1")->setProperty("text", "User " + reqs->carOwner + " agrees with you suggestion");
        root->findChild<QObject*>("respondeRentals2")->setProperty("text", "for car: " + reqs->carName);
        root->findChild<QObject*>("respondeRentals1")->setProperty("visible", true);
        root->findChild<QObject*>("respondeRentals2")->setProperty("visible", true);
        root->findChild<QObject*>("respondeRentalsButton1")->setProperty("visible", false);
        root->findChild<QObject*>("respondeRentalsButton2")->setProperty("visible", false);
    }
}

void Core::scheduler(ChatListReq* req)
{
    emit clearListChat();
    for(auto i : req->userName)
    {
        ChatInfoMsg* msg  = new ChatInfoMsg;
        msg->login = login;
        msg->carName = req->carName;
        msg->carOwner = req->carOwner;
        msg->userName = i;
        emit transmitMsg(msg);
        if(login == req->carOwner)
            emit addChatInfo(login, i);
        else
            emit addChatInfo(login, req->carOwner);
    }
    if(req->userName.size() == 0)
    {
        ChatInfoMsg* msg  = new ChatInfoMsg;
        msg->login = login;
        msg->carName = req->carName;
        msg->carOwner = req->carOwner;
        msg->userName = login;
        if(msg->login == msg->carOwner)
        {
            //emit addChatInfo(msg->carOwner, msg->userName);
        }
        else
        {
            msg->userName = login;
            emit addChatInfo(msg->login, msg->carOwner);
        }
        emit transmitMsg(msg);
    }
    delete req;
}

void Core::scheduler(ChatInfoReq* req)
{
    QString from, to;
    from = req->login;
    if(req->login == req->carOwner)
        to = req->userName;
    else
        to = req->carOwner;
    std::vector<Message> vec;
    for(auto i : req->chat)
    {
        Message msg;
        msg.from = from;
        msg.to   = to;
        msg.isMe = (from == i.first)? true : false;
        msg.text = i.second;
        vec.push_back(msg);
    }
    emit setChat(from, to, vec);
    delete req;
    if(chatReady)
    {
        zeroChat();
    }
}

void Core::scheduler(NewMsgChatReq *req)
{
    Message msg;
    msg.from = req->from;
    msg.to   = req->to;
    msg.isMe = false;
    msg.text = req->text;
    emit loadMsg(msg);
}

void Core::atemptRespond(bool is)
{
    if(is)
    {
        RentalRespondMsg* msg = new RentalRespondMsg();
        msg->login = login;
        msg->carName = reqs->carName;
        msg->carOwner = reqs->carOwner;
        msg->rentalUser = reqs->rentalUser;
        emit transmitMsg(msg);
    }
    delete reqs;
    reqs = nullptr;
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
        param.login      = login;
        emit addCar(param);
        emit transmitMsg(msg);
        emit waitingConfirm();

        emit pop();
    }
}
void Core::see(QString carsName)
{
    if(isPerson){
        seeInfoCar = seeInfoRental = true;
        CarInfoMsg* msg = new CarInfoMsg();
        msg->login = login;
        msg->carName = carsName;
        emit transmitMsg(msg);
        RentalInfoMsg* msg1 =  new RentalInfoMsg();
        msg1->login = login;
        msg1->carName = carsName;
        emit transmitMsg(msg1);
        root->findChild<QObject*>("busyIndicatorMain")->setProperty("visible", true);
        root->findChild<QObject*>("stackView")->setProperty("visible", false);
    }else
    {
        emit waitingConfirm();
    }
}
void Core::rentalMsg(QString _login, QString name, double cost)
{
    if(_login != login) return;
    ConfirmRentalMsg* msg = new ConfirmRentalMsg();
    msg->login = login;
    msg->cost = cost;
    msg->carName = name;
    QString format = "MM-dd-yyyy";
    msg->from = root->findChild<QObject*>("from")->property("fromDate").toDate().toString(format);
    msg->to   = root->findChild<QObject*>("to")->property("toDate").toDate().toString(format);
    CarRentalAd param;
    param.to = msg->to;
    param.from = msg->from;
    transmitMsg(msg);
    param.carName = name;
    param.cost = cost;
    emit addCarRentalAd(param);
    emit pop();

}
void Core::rentalRespond(QString carOwner, QString carName)
{
    RentalRespondMsg* msg = new RentalRespondMsg();
    msg->login = login;
    msg->carName = carName;
    msg->carOwner = carOwner;
    msg->rentalUser = login;
    emit transmitMsg(msg);
    emit pop();
}
void Core::pushMsg(Message _msg, QString carName)
{
    NewMsgChatMsg* msg = new NewMsgChatMsg();
    msg->login = login;
    msg->from  = _msg.from;
    msg->to    = _msg.to;
    msg->text  = _msg.text;
    msg->carName = carName;
    emit transmitMsg(msg);
}
void Core::chatUpdateList(QString carName, QString carOwner)
{
    ChatListMsg* msg = new ChatListMsg;
    msg->login = login;
    msg->carName = carName;
    msg->carOwner = carOwner;
    emit transmitMsg(msg);
}
