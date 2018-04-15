#include "mainwindow.h"
#include <QApplication>
#include "navigation.h"
#include "thread.h"
#include "connection.h"
#include "signal_temp.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mysql_connect();
    Thread thread;
    MainWindow w;
    QObject::connect(signal_temp(), &Signal_temp::notify_event_log, w.event_log, &Event_log::display_event_log);
    QObject::connect(&thread, &Thread::alarm_modify, w.alarm_list, &Alarm_list::update_data);
    QObject::connect(&thread, &Thread::alarm_occur, w.alarm_list, &Alarm_list::insert_data);
    QObject::connect(&thread, &Thread::channel_in, w.channel, &Channel::new_channel);
    QObject::connect(w.channel, &Channel::test_signal, &thread, &Thread::test_signal);
    QObject::connect(w.channel, &Channel::close_signal, &thread, &Thread::close_signal);
    QObject::connect(&thread, &Thread::remove_channel, w.channel, &Channel::remove_item);
    thread.start();

    return a.exec();
}
