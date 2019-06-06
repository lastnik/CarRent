#include "chatlistmodel.h"
ChatListModel::ChatListModel()
{
    clear();
}
QHash<int, QByteArray> ChatListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[indexRole]  = "indexRole";
    roles[to]         = "chatWithMan";
    roles[active]     = "chatActive";
    return roles;
}
QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
        case indexRole: return index.row();
        case to:        return chat[index.row()].to;
        case active:        return activeChat;
    }
    return QVariant();
}
int ChatListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return chat.size();
}

void ChatListModel::setChat(QString from, QString to, std::vector<Message> params)
{
    beginResetModel();
    for(auto& i : chat)
    {
        if(i.to == to && i.from == from)
        {
            i.chat = params;
        }
    }
    endResetModel();
}

void ChatListModel::addChatInfo(QString from,QString to)
{
    beginResetModel();
    ChatInfo info;
    info.to = to;
    info.from = from;
    chat.push_back(info);
    endResetModel();
}

void ChatListModel::clear()
{
    beginResetModel();
    emit clearChat();
    chat.clear();
    activeChat = -1;
    endResetModel();
}

void ChatListModel::confirmMsg(QString text, QString carName)
{
    if(activeChat == -1) return;
    Message msg;
    msg.to = chat[activeChat].to;
    msg.from = chat[activeChat].from;
    msg.isMe = true;
    msg.text = text;
    emit addMsg(msg);
    emit pushMsg(msg, carName);
}
void ChatListModel::loadMsg(Message msg)
{
    for(int i = 0; i < chat.size(); i++)
    {
        if(chat[i].to == msg.from && chat[i].from == msg.to)
        {
            chat[i].chat.push_back(msg);
            if(i == activeChat)
            {
                emit addMsg(msg);
            }
        }
    }
}
void ChatListModel::setActiveChat(int a)
{
    beginResetModel();
    activeChat = a;
    emit clearChat();
    if(chat.size() > activeChat)
    {
        emit setMsgs(chat[activeChat].chat);
    }
    endResetModel();
}
void ChatListModel::setFirst()
{
    activeChat = 0;
    emit clearChat();
    if(chat.size() > activeChat)
    {
        emit setMsgs(chat[activeChat].chat);
    }
}
