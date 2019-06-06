#include "rentaladmodel.h"
RentalAdModel::RentalAdModel()
{
    clear();
}
QHash<int, QByteArray> RentalAdModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[indexRole]  = "indexRole";
    roles[carName]    = "adCarName";
    roles[from]       = "adCarFrom";
    roles[to]         = "adCarTo";
    roles[carOwner]   = "adCarOwner";
    roles[cost]       = "adCarCost";
    return roles;
}
QVariant RentalAdModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
        case indexRole: return index.row();
        case carName:   return rentalParam[index.row()].carName;
        case carOwner:  return rentalParam[index.row()].carOwner;
        case from:      return rentalParam[index.row()].from;
        case to:        return rentalParam[index.row()].to;
        case cost:      return rentalParam[index.row()].cost;
    }
    return QVariant();
}
int RentalAdModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return rentalParam.size();
}
void RentalAdModel::setParams(std::vector<RentalAd> params)
{
    emit update();
    beginResetModel();
    clear();
    for(auto i : params)
    {
        rentalParam.push_back(i);
    }
    endResetModel();
    emit ready();
}
void RentalAdModel::clear()
{
    rentalParam.clear();
}
void RentalAdModel::rentalView(int i)
{
    emit see(rentalParam[i].carName);
}
