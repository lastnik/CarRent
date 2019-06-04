#ifndef CARMODEL_H
#define CARMODEL_H
#include <QObject>
#include <QAbstractListModel>
#include <QObjectList>
#include <QStringList>
#include <QDir>
#include <vector>
#include <utility>
struct CarParam
{
    QString login     = "";
    QString carName   = "";
    QString carPics   = "";
    QString carNumber = "";
    QString carOwner  = "";
    QString carBrend  = "";
    QString carModel  = "";
    QString carColor  = "";
    bool    carConfirm = false;
    bool    isLast = false;
    int     year   = 0;
    QString carState = "none";
};
class CarModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        indexRole = Qt::UserRole + 1,
        carName,
        carPics,
        carNumber,
        carOwner,
        carBrend,
        carModel,
        carColor,
        carConfirm,
        isLast,
        year
    };
    CarModel();
    void setRoot(QObject*);
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex &parent) const;
public slots:
    void addParam(CarParam param);
    void setParams(std::vector<CarParam> params);
    void clear();
    void carView(int);
    void confirmRental();
signals:
    void carRegistrationPage();
    void carPage();
    void waitingConfirm();
    void rentalMsg(QString, QString, double);
private:
    void push_back();
    std::vector<CarParam> carsParam;
    QObject*    root;
};

#endif // CARMODEL_H
