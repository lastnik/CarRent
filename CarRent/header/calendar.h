#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QDateTime>
class Calendar : public QObject
{
    Q_OBJECT
private:
    void setDate(QDateTime);
public:
    explicit Calendar(QObject *parent = nullptr);

signals:
    void newDate(QDateTime date);
public slots:

    void incMonth(QDateTime);
    void decMonth(QDateTime);
};

class SenderCalendar : public QObject
{
    Q_OBJECT
public:
    explicit SenderCalendar(QObject *parent) : QObject(parent){}
signals:
    void newDate(QDateTime date);
public slots:
    void changeDate(QDateTime);
};

#endif // CALENDAR_H
