#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H
#include <QObject>
#include <QAbstractListModel>
#include <QObjectList>
#include <QStringList>
#include <QDir>
#include <vector>
#include <utility>
class RowPics : public QObject
{
    Q_OBJECT
public:
    RowPics(QString _str1="",QString _str2="",QString _str3="")
        : str1(_str1), str2(_str2), str3(_str3)
    {
    }
    QString source1() const{return str1;}
    QString source2() const{return str2;}
    QString source3() const{return str3;}
private:
    QString str1 = "";
    QString str2 = "";
    QString str3 = "";
};


class DocumentsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        indexRole = Qt::UserRole + 1,
        source1Role,
        source2Role,
        source3Role,

    };
    DocumentsModel(QStringList& listName);
    void setRoot(QObject*);
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex &parent) const;
public slots:
    void clear();
    void setDocFile(int, QString);
    void confirm();
    void confirmCar();
    void setDocName(QStringList);
signals:
    void setVisible(int idDoc, bool vis);
    void setButton();
    void registration();
    void confirmDocs(std::vector<std::pair<QString, QString>>);
private:
    QObjectList update() const;

    QStringList documentsName;
    std::vector<std::pair<QString, QString>> documentsFile;

    QDir        pathPicture;
    QStringList pictureName;
    QObject*    root;
};

#endif // DOCUMENTSMODEL_H
