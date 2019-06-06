#pragma once
#include <QObject>
#include <QAbstractListModel>
#include <QObjectList>
#include <QStringList>
#include <QDir>
#include <vector>
#include <utility>
struct RentalAd
{
    QString carOwner  = "";
    QString carName   = "";
    QString from      = "";
    QString to        = "";
    double cost       = 0.0;
};

class RentalAdModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        indexRole = Qt::UserRole + 1,
        carName,
        carOwner,
        from,
        to,
        cost
    };
    RentalAdModel();
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex &parent) const;
public slots:
    void setParams(std::vector<RentalAd> params);
    void clear();
    void rentalView(int);
signals:
    void update();
    void ready();
    void see(QString carName);
private:
    std::vector<RentalAd> rentalParam;
};
