#include "calendar.h"
#include <QEvent>
#include <QString>
#include <QVariant>
Calendar::Calendar(QObject *parent) : QObject(parent)
{

}


void Calendar::incMonth(QDateTime oldDate)
{
    int y,m,d;
    auto a = oldDate.date();
    a.getDate(&y,&m,&d);
    if(m == 12)
    {
        m = 1;
        y++;
    }else
    {
        m++;
    }
    oldDate.setDate(QDate(y,m,d));
    setDate(oldDate);
}

void Calendar::decMonth(QDateTime oldDate)
{
    int y,m,d;
    auto a = oldDate.date();
    a.getDate(&y,&m,&d);
    if(m == 1)
    {
        m = 12;
        y--;
    }else
    {
        m--;
    }
    oldDate.setDate(QDate(y,m,d));
    setDate(oldDate);
}
void Calendar::setDate(QDateTime Date)
{
    QString format = "MMMM yyyy";

    parent()->findChild<QObject*>("str")->setProperty("text", Date.toString(format));
    auto* spaceCalendar = parent()->findChild<QObject*>("grid");
    spaceCalendar->setProperty("local", Date);
}
void SenderCalendar::changeDate(QDateTime NewDate)
{
    emit newDate(NewDate);
}
