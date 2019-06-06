#pragma once
#include <QObject>
#include <QAbstractListModel>
#include <QObjectList>
#include <QStringList>
#include <QDir>
#include <vector>
#include <utility>
struct Message{
    QString from;
    QString to;
    bool    isMe;
    QString text;
};

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        indexRole = Qt::UserRole + 1,
        isMe,
        text,
        from,
        to
    };
    ChatModel();
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex &parent) const;
public slots:
    void setMsgs(std::vector<Message> params);
    void addMsg(Message params);
    void clear();
    //void chatPush(QString);
signals:
    void setLast();
    void sendMsg();
private:
    std::vector<Message> chat;

};
