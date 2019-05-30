#include <QCoreApplication>
#include "servernet.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ServerNet serv;
    return a.exec();
}
