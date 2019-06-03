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
    QString carName;
    QString carPics;
    QString carNumber;
    QString carOwner;
    bool    carConfirm;
    bool    isLast;
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
        carConfirm,
        isLast
    };
    CarModel(std::vector<QString> listName);
    void setRoot(QObject*);
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex &parent) const;
public slots:
    void setInfo(CarParam param);
    void setParams(std::vector<CarParam> params);
    void clear();
signals:

private:
    void push_back();
    std::vector<CarParam> carsParam;
    QObject*    root;
};

#endif // CARMODEL_H
