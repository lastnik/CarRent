#pragma once
#include <QObject>
#include <QAbstractListModel>
#include <QObjectList>
#include <QStringList>
#include <QDir>
#include <vector>
#include <utility>
#include "chatmodel.h"
struct ChatInfo{
    QString from;
    QString to;
    std::vector<Message> chat;
};

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        indexRole = Qt::UserRole + 1,
        to,
        active
    };
    ChatListModel();
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex &parent) const;
public slots:
    void addChatInfo(QString, QString);
    void setChat(QString, QString, std::vector<Message> params);
    void clear();
    void setFirst();
    void confirmMsg(QString, QString);
    void loadMsg(Message);
    void setActiveChat(int);
signals:
    void addMsg(Message);
    void pushMsg(Message, QString);
    void clearChat();
    void setMsgs(std::vector<Message> params);
private:
    std::vector<ChatInfo> chat;
    int                   activeChat = -1;
};
