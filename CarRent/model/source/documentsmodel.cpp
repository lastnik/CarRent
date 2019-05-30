#include "documentsmodel.h"
#include <string>
DocumentsModel::DocumentsModel(QStringList& listName)
    : QAbstractListModel (nullptr)
    , documentsName(listName)
    , pathPicture("C:/Users/lastochk/Pictures")
{
}

void DocumentsModel::setRoot(QObject* _root)
{
    root = _root;
}
QHash<int, QByteArray> DocumentsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[indexRole] = "indexRole";
    roles[source1Role] = "source1Role";
    roles[source2Role] = "source2Role";
    roles[source3Role] = "source3Role";
    return roles;
}
QObjectList DocumentsModel::update() const
{
    QObjectList list;
    auto listFiles = pathPicture.entryList(QStringList("*"), QDir::Files);
    QString row[3] = {"","",""};
    size_t flag = 0;
    for(auto i : listFiles)
    {
        if(i.toStdString().find(".png") != std::string::npos
                || i.toStdString().find(".jpg") != std::string::npos
                        || i.toStdString().find(".jpeg") != std::string::npos)
        {
            row[flag] = i;
            flag++;
        }
        if(flag == 3)
        {
            flag %= 3;
            list.append(new RowPics( pathPicture.absolutePath() + "/" + row[0]
                                   , pathPicture.absolutePath() + "/" + row[1]
                                   , pathPicture.absolutePath() + "/"  + row[2]));
            for(size_t k = 0; k < 3; k++) row[k] = "";
        }
    }
    if(flag == 1)
    {
        list.append(new RowPics(pathPicture.absolutePath() + "/" + row[0]));
    }else
    if(flag == 2)
    {
        list.append(new RowPics( pathPicture.absolutePath() + "/" + row[0]
                               , pathPicture.absolutePath() + "/" + row[1]));
    }
    return list;
}
QVariant DocumentsModel::data(const QModelIndex &index, int role) const
{
    auto list = update();
    switch(role)
    {
        case indexRole: return index.row();
        case source1Role: return reinterpret_cast<RowPics*>(list.at(index.row()))->source1();
        case source2Role: return reinterpret_cast<RowPics*>(list.at(index.row()))->source2();
        case source3Role: return reinterpret_cast<RowPics*>(list.at(index.row()))->source3();
    }
    return QVariant();
}
int DocumentsModel::rowCount(const QModelIndex &parent) const
{
    auto list = update();
    if (parent.isValid()) {
        return 0;
    }

    return list.size();
}

void DocumentsModel::setDocFile(int idDoc, QString docFile)
{
    for(auto i : documentsFile)
    {
        if(i.second == docFile && i.first == documentsName.at(idDoc))
        {
            emit setVisible(idDoc, true);
            return;
        }
        if(i.first == documentsName.at(idDoc))
        {
            i.second = docFile;
            emit setVisible(idDoc, true);
            return;
        }
    }
    documentsFile.push_back(std::make_pair(documentsName.at(idDoc), docFile));
    emit setVisible(idDoc, true);
    if(documentsFile.size() == documentsName.size())
    {
        emit setButton();
    }
}

void DocumentsModel::clear()
{
    documentsFile.clear();
    for(int idDoc = 0; idDoc < documentsName.size(); idDoc++)
        emit setVisible(idDoc, false);
}

void DocumentsModel::confirm()
{
    emit confirmDocs(documentsFile);
    clear();
}
void DocumentsModel::setDocName(QStringList list)
{
    documentsName = list;
}
