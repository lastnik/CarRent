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
    roles[indexRole] = "indexRole";
    roles[carName] = "carName";
    roles[carPics] = "carPics";
    roles[carNumber] = "carNumber";
    roles[carOwner] = "carOwner";
    roles[carConfirm] = "carConfirm";
    roles[isLast] = "isLast";
    return roles;
}
QVariant CarModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case indexRole: return index.row();
        case carName:   return carsParam[index.row()].carName;
        case carPics:   return carsParam[index.row()].carPics;
        case carNumber: return carsParam[index.row()].carNumber;
        case carOwner:  return carsParam[index.row()].carOwner;
        case carConfirm:return carsParam[index.row()].carConfirm;
        case isLast:    return carsParam[index.row()].isLast;
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
    clear();
    bool first = true;
    for(auto i : listName)
    {
        if(first)
        {
            carsParam[carsParam.size() - 1] = i;
            first =false;
        }
        else
            carsParam.push_back(i);
    }
    push_back();
}


void CarModel::carView(int id)
{
    if(id == carsParam.size() - 1)
    {
        emit carRegistrationPage();
    }else
    {

    }
}

void CarModel::setInfo(CarParam param)
{
    carsParam.push_back(param);
}

void CarModel::clear()
{
    carsParam.clear();
    push_back();
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
