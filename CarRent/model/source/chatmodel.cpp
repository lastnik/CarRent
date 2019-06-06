#include "chatmodel.h"
ChatModel::ChatModel()
{
    clear();
}
QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[indexRole]  = "indexRole";
    roles[isMe]    = "chatIsMe";
    roles[from]    = "chatIsFrom";
    roles[to]      = "chatIsTo";
    roles[text]    = "chatIsText";
    return roles;
}
QVariant ChatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
        case indexRole: return index.row();
        case isMe:      return chat[index.row()].isMe;
        case from:      return chat[index.row()].from;
        case to:        return chat[index.row()].to;
        case text:      return chat[index.row()].text;
    }
    return QVariant();
}
int ChatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return chat.size();
}
void ChatModel::setMsgs(std::vector<Message> params)
{
    beginResetModel();
    clear();
    for(auto i : params)
    {
        chat.push_back(i);
    }
    emit setLast();
    endResetModel();
}
void ChatModel::clear()
{
    beginResetModel();
    chat.clear();
    endResetModel();
}
void ChatModel::addMsg(Message msg)
{
    beginResetModel();
    chat.push_back(msg);
    emit setLast();
    endResetModel();
}

