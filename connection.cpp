#include "connection.h"
#include <QtSql>
#include <QMessageBox>
void mysql_connect(){
    QSqlDatabase d = QSqlDatabase::addDatabase("QMYSQL");
    d.setDatabaseName("alarm");
    d.setHostName("127.0.0.1");
    d.setPort(3306);
    d.setUserName("root");
    d.setPassword("wang1111");
    if(!d.open()){
        QMessageBox::critical(nullptr, "connect mysql database Error", "connect mysql database Error");
	}
	else{
	QSqlQuery query;
	query.exec("delete from alarm_list;");
	query.exec("delete from channel;");
	}
}
bool sql_exec(const QString& s){
    QSqlQuery query;
    if(!query.exec(s)){
        QMessageBox::critical(nullptr, "exec sql Error:", s + "\n" + query.lastError().text());
        return false;
    }
    return true;
}


void set_row_color(QTreeWidgetItem *item, const QString & color){
    int count = item->columnCount();
    for(int i=0; i<count; i++){
        item->setBackground(i, QBrush(QColor(color)));
    }
}
Connection::Connection(QTcpSocket* p, int a, int* x) {
    socket = p;
    id = a;
    now = x;
    if(socket->waitForReadyRead() && socket->isValid()){
        QString temp(QByteArray(socket->read(1024)));
        QStringList list = temp.split(' ',QString::SkipEmptyParts);
        for(QString x:list){
            alarm.append(x.toInt());
        }
        sql_exec("insert into channel value(" + QString::number(id, 10) +
                             ", '" + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "','" + temp + "'," + "1"+ ");" );

    }
    connect(socket, &QTcpSocket::readyRead, this, &Connection::data_in);
    connect(socket, &QTcpSocket::disconnected, this, &Connection::send_disconnected);
}

void Connection::data_in(){
    if(!socket->isValid())
        return;
    QString temp(QByteArray(socket->read(1024)));
    QStringList list = temp.split(' ', QString::SkipEmptyParts);
    int status = list[1].toInt();
    QSqlQuery ex;
    if(!ex.exec("select status from alarm where alarm_id = " + list[0] +";")){
        QMessageBox::critical(nullptr, "sql exec error:","select status from alarm where alarm_id = " + list[0] +";"+ "\n" + ex.lastError().text());
    }
    if(ex.next()){
        if(ex.value(0).toString() == "0")
            return;
    }
    else{
        qDebug()<<"not find alarm in alarm table";
        return;
    }
    if(list.size() == 2){//产生报警项
        sql_exec("insert into alarm_list(id, alarm_id, ack, status, time) value("+QString::number(*now, 10) +", " + list[0] + ", 1, " + list[1] + ",'" +
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "');");
        int number = *now;
        int id_temp = *now;
        *now = *now + 1;
        QVector<int> num;
        while(number>0){
            num.append(number%10);
            number = number/10;
        }
        char* result = new char[num.size()+1];
        for(int i=0; i<num.size(); i++)
            result[i] = num[num.size() - i -1] + 48;
        result[num.size()] = 0;
        if( !(socket->isValid() && socket->write(result, num.size()+1) > 0))
            qDebug()<<"can not write "<<result;
        delete[] result;
        emit alarm_occur(id_temp);
    }
    else if(list.size() == 3){//修改报警项
        if(status == 6 || status == 7) //ignore cut out alarm
            return;
        QSqlQuery query;
        if(!query.exec("select status from alarm_list where id=" + list[2] +";")){
            QMessageBox::critical(nullptr, "exec sql Error:",
                                  "select status from alarm_list where id=" + list[2] +";"
                                  + "\n" + query.lastError().text());
            return;
        }
        int ack;
        if (query.next())
            if(query.value(0).toInt() == 1 && status==5)
                ack = 7;
            else if(query.value(0).toInt() == 2 && status==5)
                ack = 6;
            else{
                ;
            }
        else
            QMessageBox::critical(nullptr, "select data Error:", "select status from alarm_list where id=" + list[2] +";");
        if(status == 1)
            ack = 2;
        sql_exec("update alarm_list set status=" + list[1] + ", ack=" + QString::number(ack, 10) +", time='" +
                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "' where id=" + list[2] + ";");
        emit alarm_modify(list[2].toInt());
    }
    else
        QMessageBox::critical(nullptr, "alarm data transmisson Error:", "alarm device not obey data transmisson protocol");
}

void Connection::send_disconnected(){
    emit not_connected(id);
}

Connection::~Connection(){
//    socket->~QTcpSocket();
}
