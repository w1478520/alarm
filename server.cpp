#include "server.h"
#include "alarm_list.h"
#include "connection.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
Server::Server(QObject *parent):QTcpServer(parent){
    connect(this, &QTcpServer::newConnection, this, &Server::get_connection);
    tag.resize(1000);
    for(int i=0; i<tag.size(); i++)
        tag[i] = true;
    connections.resize(1000);
    now = new int;
    *now = 1;
}

void Server::get_connection(){
    QTcpSocket* temp = nextPendingConnection();
    int local = -1;
    for(int i=1; i<tag.size(); i++){
        if(tag[i] == true){
            local = i;
            tag[i] = false;
            break;
        }
    }
    if(local == -1)
        qDebug()<<"It is more than 1000 channel, please try to modify the code";
    Connection* child = new Connection(temp, local, now);
    emit channel_in(local);
    connections[local] = child;
    connect(child, &Connection::alarm_modify, this, &Server::alarm_modify);
    connect(child, &Connection::alarm_occur, this, &Server::alarm_occur);
    connect(child, &Connection::not_connected, this, &Server::close_channel);
}

void Server::close_channel(int channel_id){
    Connection* p = connections[channel_id];
    if(p->socket->state() != QAbstractSocket::UnconnectedState)
        p->socket->close();
    if(connections[channel_id]){
//      QSqlQuery query;
//      if(!query.exec("select * from event_log where description = 'channel id is " + QString::number(channel_id) + "';"))
//          QMessageBox::critical(nullptr, "exec sql Error:", "select class in event_log where event_id =" + QString::number(channel_id) + ";" + "\n" + query.lastError().text());
//      if(!query.next())
//          event_log(4, "the channel id is " + QString::number(channel_id));
        delete p;
        p = nullptr;
        connections[channel_id] = nullptr;
        tag[channel_id] = true;
    }
    sql_exec("delete from channel where channel_id =" + QString::number(channel_id, 10) + ";");
    emit remove_channel(channel_id);
}

void Server::test_channel(int channel_id){
    Connection* p = connections[channel_id];
    if(p->socket->waitForBytesWritten() && p->socket->isValid()){
        if(p->socket->write("test")>0)
            return;
        else{
            event_log(5,"channel id is " + QString::number(channel_id));
            close_channel(channel_id);
        }
    }
}
