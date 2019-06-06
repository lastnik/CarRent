#include "carmodel.h"

CarModel::CarModel()
{
    clear();
}

void CarModel::setRoot(QObject* _root)
{
    root = _root;
}

QHash<int, QByteArray> CarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[indexRole]  = "indexRole";
    roles[carName]    = "carName";
    roles[carPics]    = "carPics";
    roles[carNumber]  = "carNumber";
    roles[carOwner]   = "carOwner";
    roles[carBrend]   = "carBrend";
    roles[carModel]   = "carModel";
    roles[carColor]   = "carColor";
    roles[carConfirm] = "carConfirm";
    roles[isLast]     = "isLast";
    roles[year]       = "year";
    return roles;
}
QVariant CarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
        case indexRole: return index.row();
        case carName:   return carsParam[index.row()].carName;
        case carPics:   return carsParam[index.row()].carPics;
        case carNumber: return carsParam[index.row()].carNumber;
        case carOwner:  return carsParam[index.row()].carOwner;
        case carBrend:  return carsParam[index.row()].carBrend;
        case carModel:  return carsParam[index.row()].carModel;
        case carColor:  return carsParam[index.row()].carColor;
        case carConfirm:return carsParam[index.row()].carConfirm;
        case isLast:    return carsParam[index.row()].isLast;
        case year:      return carsParam[index.row()].year;

    }
    return QVariant();
}
int CarModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return carsParam.size();
}
void CarModel::setParams(std::vector<CarParam> listName)
{
    beginResetModel();
    clear();
    bool first = true;
    for(auto i : listName)
    {
        if(first)
        {
            carsParam[carsParam.size() - 1] = i;
            first = false;
        }
        else
            carsParam.push_back(i);
    }
    push_back();
    endResetModel();
}


void CarModel::carView(int id)
{
    if(id == carsParam.size() - 1)
    {
        emit carRegistrationPage();
    }else
    {
        emit chatUpdate(carsParam[id].carName, carsParam[id].carOwner);
        CarRentalAd ad;
        for(auto& i : carsRentalAd)
        {
            if(i.carName == carsParam[id].carName)
            {
                ad = i;
                break;
            }
        }
        if(carsParam[id].carConfirm)
        {
            root->setProperty("_carOwner",   carsParam[id].carOwner);
            root->setProperty("_carName",    carsParam[id].carName);
            root->setProperty("_carBrend",   carsParam[id].carBrend);
            root->setProperty("_carModel",   carsParam[id].carModel);
            root->setProperty("_carColor",   carsParam[id].carColor);
            root->setProperty("_carNumber",  carsParam[id].carNumber);
            root->setProperty("_carPics",    QString(PATH) + "/cache/" + carsParam[id].carPics);
            root->setProperty("_carConfirm", carsParam[id].carConfirm);
            root->setProperty("_login",      carsParam[id].login);
            root->setProperty("_year",       carsParam[id].year);
            root->setProperty("_carCost",    ad.cost);
            root->setProperty("_carFrom",    ad.from);
            root->setProperty("_carTo",      ad.to);
            root->setProperty("_buttonVisible", false);
            root->setProperty("_multiplyChatWindow", true);
            if(carsParam[id].carState == "free")
            {
                 root->setProperty("_visFrame", true);
                 root->setProperty("_visRental", true);
            }else
            {
                if(carsParam[id].carState == "none")
                {
                    root->setProperty("_visFrame", true);
                    root->setProperty("_visRental", false);
                }else
                {
                    if(carsParam[id].carState == "rental")
                    {
                        root->setProperty("_visFrame", false);
                        root->setProperty("_visRental", true);
                    }
                }
            }
            emit carPage();
        }else
        {
            emit waitingConfirm();
        }
    }
}

void CarModel::confirmRental()
{
    QString owner = root->property("_carOwner").toString();
    QString name = root->property("_carName").toString();
    QString login = root->property("_login").toString();
    double cost = root->property("_cost").toDouble();
    if(login == owner)
    {
        emit rentalMsg(login, name, cost);
    }
    for(auto& i : carsParam)
    {
        if(i.carName == name)
        {
            i.carState == "free";
            break;
        }
    }
}

void CarModel::addParam(CarParam param)
{
    beginResetModel();
    bool in = false;
    for(auto& i : carsParam)
    {
        if(i.carName == param.carName)
        {
            i = param;
            in = true;
        }
    }
    if(!in)
    {
        carsParam[carsParam.size() - 1] = param;
        push_back();
    }
    endResetModel();
}

void CarModel::addCarRentalAd(CarRentalAd param)
{
    bool in = false;
    for(auto& i : carsRentalAd)
    {
        if(i.carName == param.carName)
        {
            i = param;
            in = true;
        }
    }
    if(!in)
    {
        carsRentalAd.push_back(param);
    }
}


void CarModel::clear()
{
    //beginResetModel();
    carsParam.clear();
    push_back();
    //endResetModel();
}

void CarModel::push_back()
{
    CarParam add;
    add.carName = "";
    add.carPics = "";
    add.carNumber = "";
    add.carOwner = "";
    add.carConfirm = false;
    add.isLast     = true;
    carsParam.push_back(add);
}
