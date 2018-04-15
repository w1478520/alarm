#ifndef CONNECTION_H
#define CONNECTION_H
#include <QObject>
#include <QTcpSocket>
#include <QTreeWidgetItem>
#include <signal_temp.h>
Signal_temp* signal_temp();
void mysql_connect();
bool sql_exec(const QString& s);
char* ntoc(int);
void set_row_color(QTreeWidgetItem* item, const QString&);
void event_log(int, QString);
QString class_num_to_string(int);
int class_string_to_id(QString);
class Connection:public QObject{
    Q_OBJECT
public:
    Connection(QTcpSocket*, int, int*);
    ~Connection();
    void data_in();
    QTcpSocket* socket;
    void send_disconnected();
signals:
    void alarm_modify(int);
    void alarm_occur(int);
    void not_connected(int);
private:
    int id;
    QVector<int> alarm;
    int *now;
};


#endif // CONNECTION_H
