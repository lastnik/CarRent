#ifndef IMSG_H
#define IMSG_H
#include <QJsonObject>
#include <QObject>
struct IMsg : public QObject
{
    Q_OBJECT
public:
    virtual QJsonObject toJsonObject()=0;
    QString msgName;
    QString transmiterName;
};

struct IReq : public QObject
{
    Q_OBJECT
public:
    virtual QJsonObject toJsonObject()=0;
    QString reqName;
    QString receiverName;
};

#endif // IMSG_H
