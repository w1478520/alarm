#ifndef SERVER_H
#define SERVER_H
#define BUFFERSIZE 1024000
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include "connection.h"

class Server: public QTcpServer{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    void get_connection();
    void test_channel(int);
    void close_channel(int);
    void test();
signals:
    void alarm_modify(int);
    void alarm_occur(int);
    void channel_in(int);
    void remove_channel(int);
private:
    QVector<Connection*> connections;
    QVector<bool> tag;
    int* now;
};
#endif // SERVER_H
