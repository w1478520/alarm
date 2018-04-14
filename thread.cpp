#include "thread.h"
#include "server.h"
void Thread::run(){
    qDebug()<<"in thread";
    Server s;
    connect(&s, &Server::alarm_modify, this, &Thread::alarm_modify);
    connect(&s, &Server::alarm_occur, this, &Thread::alarm_occur);
    connect(&s, &Server::channel_in, this, &Thread::channel_in);
    connect(this, &Thread::close_signal, &s, &Server::close_channel);
    connect(this, &Thread::test_signal, &s, &Server::test_channel);
    connect(&s, &Server::remove_channel, this, &Thread::remove_channel);
    QHostAddress addr("127.0.0.1");
    s.listen(addr, 60000);
    exec();
}

